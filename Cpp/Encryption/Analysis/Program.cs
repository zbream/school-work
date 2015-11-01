using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Numerics;

namespace Analysis
{
    class Program
    {
        enum Algorithm { Invalid = 0, DES = 8, AES = 16 };

        static void Main(string[] args)
        {
            // check command-line parameters
            if (args.Length != 2)
            {
                Console.WriteLine("Incorrect input parameters.");
                return;
            }

            // check for algorithm
            Algorithm algorithm = Algorithm.Invalid;
            switch (args[0].ToLower())
            {
                case "des":
                    algorithm = Algorithm.DES;
                    break;
                case "aes":
                    algorithm = Algorithm.AES;
                    break;
                default:
                    Console.WriteLine("Incorrect encryption algorithm: {0}", args[0]);
                    return;
            }

            // check for input file
            FileInfo inFile = new FileInfo(args[1]);
            if (!inFile.Exists)
            {
                Console.WriteLine("Unable to find input file: {0}", args[0]);
                return;
            }

            // and open
            using (FileStream inStream = inFile.OpenRead())
            {
                // get output directory
                DirectoryInfo outDir = Directory.CreateDirectory(Path.Combine(inFile.DirectoryName, "output", inFile.Name));

                // bit frequency (0/1)
                using (FileStream outStream = File.Create(Path.Combine(outDir.FullName, "bit.csv")))
                {
                    BitAnalysis(inStream, outStream);
                }

                // letter frequency (1gram), digram through 8-gram analysis
                for (int i = 1; i <= 3; i++)
                {
                    using (FileStream outStream = File.Create(Path.Combine(outDir.FullName, i + "grams.csv")))
                    {
                        NgramAnalysis(inStream, outStream, i);
                    }
                }

                // block (8-byte or 16-byte) analysis
                using (FileStream outStream = File.Create(Path.Combine(outDir.FullName, "block.csv")))
                {
                    BlockAnalysis(inStream, outStream, (int)algorithm);
                }
            }

            return;
        }

        #region Analysis
        static void NgramAnalysis(FileStream input, FileStream output, int n)
        {
            input.Position = 0;

            Dictionary<BigInteger, int> ngrams = new Dictionary<BigInteger, int>();
            byte[] ngram = new byte[n];
            int read;

            // initialize the ngram for the loop
            for (int i = 1; i < n; i++)
            {
                if ((read = input.ReadByte()) == -1)
                {
                    // not enough characters to fill the ngram, return
                    return;
                }
                ngram[i] = (byte)read;
            }

            // slide through every ngram from the file
            while ((read = input.ReadByte()) != -1)
            {
                // shift all elements up one
                for (int i = 0; i < n - 1; i++)
                {
                    ngram[i] = ngram[i + 1];
                }
                ngram[n - 1] = (byte)read;

                // increment the count for that ngram
                BigInteger index = N2I(ngram);
                if (!ngrams.ContainsKey(index))
                {
                    ngrams.Add(index, 1);
                }
                else
                {
                    ngrams[index]++;
                }
            }

            // output the table
            using (StreamWriter outStream = new StreamWriter(output, System.Text.Encoding.ASCII))
            {
                //// this will go through every possible ngram
                //for (BigInteger i = 0; i < ((BigInteger)1 << (8 * n)); i++)
                //{
                //    // get the count for that ngram
                //    I2N(i, ngram);
                //    if (!isValidAscii(ngram)) continue;
                //    int ngramCount = ngrams.ContainsKey(i) ? ngrams[i] : 0;
                //    if (ngramCount == 0) continue;
                //    string ngramString = string.Concat(ngram.Select(escapeChar));
                //    write(outStream, ngramString, ngramCount);
                //}

                // this will go through every FOUND ngram
                foreach (var item in ngrams.OrderByDescending(kvp => kvp.Value))
                {
                    // get the count for that ngram
                    I2N(item.Key, ngram);
                    int ngramCount = item.Value;
                    string ngramString = string.Concat(ngram.Select(escapeChar));
                    write(outStream, ngramString, ngramCount);
                }
            }
        }

        static void BlockAnalysis(FileStream input, FileStream output, int blockSize)
        {
            input.Position = 0;

            Dictionary<BigInteger, int> ngrams = new Dictionary<BigInteger, int>();
            byte[] ngram = new byte[blockSize];
            int read;

            bool hasMore = true;
            while (true)
            {
                for (int i = 0; i < blockSize; i++)
                {
                    if ((read = input.ReadByte()) == -1)
                    {
                        // not enough characters to fill the block, continue
                        hasMore = false;
                        break;
                    }
                    ngram[i] = (byte)read;
                }

                if (!hasMore)
                {
                    break;
                }

                // increment the count for that ngram
                BigInteger index = N2I(ngram);
                if (!ngrams.ContainsKey(index))
                {
                    ngrams.Add(index, 1);
                }
                else
                {
                    ngrams[index]++;
                }
            }

            // output the table
            using (StreamWriter outStream = new StreamWriter(output, System.Text.Encoding.ASCII))
            {
                // this will go through every FOUND ngram
                foreach (var item in ngrams.OrderByDescending(kvp => kvp.Value))
                {
                    // get the count for that ngram
                    I2N(item.Key, ngram);
                    int ngramCount = item.Value;
                    string ngramString = string.Concat(ngram.Select(escapeChar));
                    write(outStream, ngramString, ngramCount);
                }
            }
        }

        static void BitAnalysis(FileStream input, FileStream output)
        {
            input.Position = 0;

            int[] bits = new int[2];
            int read;

            // go through every byte of the file
            while ((read = input.ReadByte()) != -1)
            {
                // go through every bit of the byte
                for (int i = 0; i < 8; i++)
                {
                    bits[read & 0x1]++;
                    read >>= 1;
                }
            }

            // output the table
            using (StreamWriter outStream = new StreamWriter(output, System.Text.Encoding.ASCII))
            {
                for (int i = 0; i <= 1; i++)
                {
                    write(outStream, i, bits[i]);
                }
            }
        }
        #endregion

        #region Utils
        const char DELIMITER = ',';
        const char QUALIFIER = '"';
        static void write(StreamWriter outStream, object left, object right)
        {
            outStream.WriteLine("{0}{2}{0}{1}{0}{3}{0}", QUALIFIER, DELIMITER, left.ToString(), right.ToString());
        }

        static string escapeChar(byte ascii)
        {
            string output;

            if (ascii >= 0x20 && ascii <= 0x7e)
            {
                // printable char
                if (ascii == QUALIFIER)
                {
                    // qualifier, duplicate
                    output = new string(QUALIFIER, 2);
                }
                else
                {
                    output = new string((char)ascii, 1);
                }
            }
            else
            {
                // non-printable char, escape as hex string
                output = string.Format("\\{0:x2}", ascii);
            }

            return output;
        }

        // ngram to index
        static BigInteger N2I(byte[] ngram)
        {
            BigInteger output = new BigInteger();

            for (int i = 0; i < ngram.Length; i++)
            {
                output <<= 8;
                output |= ngram[i];
            }

            return output;
        }

        // index to ngram
        static void I2N(BigInteger index, byte[] ngram)
        {
            for (int i = ngram.Length - 1; i >= 0; i--)
            {
                ngram[i] = (byte)(index & 0xFF);
                index >>= 8;
            }
        }

        static bool isValidAscii(byte[] ngram)
        {
            for (int i = 0; i < ngram.Length; i++)
            {
                if (ngram[i] > 0x7F)
                {
                    return false;
                }
            }
            return true;
        }
        #endregion
    }
}
