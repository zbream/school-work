public class MainClass
{

	public static void main(String[] args)
	{
		int length = 4000;
		int[] array = new int[length];
		for(int x = 0; x < length; x++)
		{
			array[x] = x;
		}
		System.out.println(sum(array));
		System.out.println(sumR(array));
		System.out.println(sumRR(array, 0));
	}

	static long sum(int[] array)
	{
		long result = 0;
		for (int x = 0; x < array.length; x++)
		{
			result += array[x];
		}
		return result;
	}

	static long sumR(int[] array)
	{
		int x;
		if (array.length == 1)
		{
			return array[0];
		} else
		{
			int[] trimmed = new int[array.length - 1];
			for (x = 0; x < array.length - 1; x++)
			{
				trimmed[x] = array[x];
			}
			return (array[x] + sumR(trimmed));
		}
	}
	
	static long sumRR(int[] array, int index)
	{
		if(index == array.length)
		{
			return 0;
		}
		else
		{
			return array[index] + sumRR(array, index + 1);
		}
	}
}
