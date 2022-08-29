using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Threading;

namespace trivia_client
{
    /// <summary>
    /// Interaction logic for Question.xaml
    /// </summary>
    public partial class Question : Page
    {
        private Communicator _com;
        private MenuWindow wnd;
        private int time;
        private string question;
        private List<string> answers;
        private int currentTime;
        private bool isCorrect;
        private bool isAnswered;
        private int questionId;
        private int numberOfQuestions;
        private readonly object locker = new object();

        public Question(Communicator com, MenuWindow wnd, int time, string question, List<string> answers, int questionId, int num)
        {
            InitializeComponent();
            this.questionId = questionId;
            this.numberOfQuestions = num;
            this.time = time;
            this.question = question;
            this.answers = answers;
            this._com = com;
            this.wnd = wnd;
            this.currentTime = DateTime.Now.Second;
            this.isCorrect = false;
            this.isAnswered = false;

            MyQuestion.Content = this.question;
            First.Content = this.answers[0];
            Second.Content = this.answers[1];
            Third.Content = this.answers[2];
            Fourth.Content = this.answers[3];


            Thread timer = new Thread(TimeCounter);
            timer.Start();
        }

        private void OnExitClick(object sender, RoutedEventArgs e)
        {
            try
            {
                lock (this.locker)
                {
                    GameResponeHandler.leaveGame(this._com);
                }
                wnd.ChangeToMenu(this._com, "", wnd);
            }
            catch
            {
                wnd.ChangeToError(wnd);
            }
        }

        public void OnSubmitClick(object sender, RoutedEventArgs e)
        {
            SubmitAnswerRequest myAnswer;

            int currentTime = DateTime.Now.Second;
            if (currentTime <= this.currentTime)
                myAnswer.time = Constants.SEC_IN_MIN - this.currentTime + currentTime;
            else
                myAnswer.time = currentTime - this.currentTime;

            if (First.IsChecked == true)
                myAnswer.answer = First.Content.ToString();
            else if (Second.IsChecked == true)
                myAnswer.answer = Second.Content.ToString();
            else if (Third.IsChecked == true)
                myAnswer.answer = Third.Content.ToString();
            else
                myAnswer.answer = Fourth.Content.ToString();

            try
            {
                lock (this.locker)
                {
                    this.isCorrect = GameResponeHandler.SubmitAnswer(myAnswer, this._com).isAnswerCorrect;
                    this.isAnswered = true;
                    Feedback.Content = "Wait for reveal";
                }
            }
            catch
            {
                wnd.ChangeToError(wnd);
            }
        }

        public void EndRunning(object sender, RoutedEventArgs e)
        {
            try
            {
                lock (this.locker)
                {
                    GameResponeHandler.leaveGame(this._com);
                    MenuResponeHandler.LogOut(this._com);
                    System.Windows.Application.Current.Shutdown();
                }
            }
            catch
            {
                wnd.ChangeToError(wnd);
            }
        }

        public void TimeCounter()
        {
            SubmitAnswerRequest myAnswer;
            GetQuestionResponse questionResp;
            int i = 0;
            for (i = time; i >= 0; i--)
            {
                this.Dispatcher.Invoke(() =>
                {
                    Timer.Content = "Time: " + i.ToString();
                });
                Thread.Sleep(1000);
            }
            if (!this.isAnswered)
            {
                myAnswer.answer = "";
                myAnswer.time = this.time;

                try
                {
                    lock (this.locker)
                    {
                        GameResponeHandler.SubmitAnswer(myAnswer, this._com);
                    }
                }
                catch
                {
                    wnd.ChangeToError(wnd);
                }
            }
            if (this.isCorrect)
            {
                this.Dispatcher.Invoke(() =>
                {
                    Feedback.Content = "Well done! Correct ans";
                });
            }
            else
            {
                this.Dispatcher.Invoke(() =>
                {
                    Feedback.Content = "Sorry, Wrong ans";
                });
            }
            Thread.Sleep(2000);
            if (questionId != numberOfQuestions)
            {
                try
                {
                    lock (this.locker)
                    {
                        questionResp = GameResponeHandler.getNextQuestion(this._com);
                    }
                    this.Dispatcher.Invoke(() =>
                    {
                        wnd.ChangeToQuestion(time, questionResp.question, questionResp.Answers, this._com, wnd, questionId++, numberOfQuestions);
                    });
                }
                catch
                {
                    this.Dispatcher.Invoke(() =>
                    {
                        wnd.ChangeToError(wnd);
                    });
                }
            }
            else
            {
                // add a page that will be the end game
            }
        }
    }
}
