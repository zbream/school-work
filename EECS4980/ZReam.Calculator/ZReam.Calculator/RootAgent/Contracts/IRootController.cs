namespace ZReam.Calculator.RootAgent.Contracts
{
    interface IRootController
    {
        void Shutdown();

        void ToggleSpeechInput(bool enable);

        void ToggleSpeechOutput(bool enable);

        void Calculate(string inputString);

        void RepeatOutput();
    }
}
