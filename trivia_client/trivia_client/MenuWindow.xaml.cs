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
using System.Windows.Shapes;

namespace trivia_client
{
    /// <summary>
    /// Interaction logic for MenuWindow.xaml
    /// </summary>
    public partial class MenuWindow : Window
    {
		Communicator _com;
		string username;

		public MenuWindow(Communicator com, string username)
		{
			InitializeComponent();
			this.Content = new MenuPage(com, username, this);
			this._com = com;
			this.username = username;
		}

		public void ChangeToLobby(bool isLeader, string username, string roomId, string roomName, string timeBetweenQuestions, string difficulty, string numOfQuestions, Communicator com, MenuWindow wnd)
		{
			this.Content = new LobbyRoom(isLeader, username, roomId, roomName, timeBetweenQuestions, difficulty, numOfQuestions, com, wnd);
		}

		public void ChangeToMenu(Communicator com, string username, MenuWindow wnd)
		{
			this.Content = new MenuPage(com, username, wnd);
		}
		public void ChangeToStatistics(Communicator com, MenuWindow wnd)
		{
			this.Content = new Statistics(com, wnd);
		}

		public void ChangeToError(MenuWindow wnd)
		{
			this.Content = new ErrorPage(wnd);
		}

		public void ChangeToQuestion(int time, string question, List<string> answers, Communicator com, MenuWindow wnd, int questionId, int numberOfQuestions)
		{
			this.Content = new Question(com, wnd, time, question, answers, questionId, numberOfQuestions);
		}

		private void Window_MouseDown(object sender, MouseButtonEventArgs e)
		{
			if (e.ChangedButton == MouseButton.Left)
				this.DragMove();
		}
	}
}
