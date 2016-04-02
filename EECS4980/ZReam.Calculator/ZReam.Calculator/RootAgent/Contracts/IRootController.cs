namespace ZReam.Calculator.RootAgent.Contracts
{
    interface IRootController
    {
        void Shutdown();

        void ToggleSpeechInput(bool enable);

        void ToggleSpeechOutput(bool enable);

        void NewInput(string inputString);

        void RepeatSpeech();
    }
}
