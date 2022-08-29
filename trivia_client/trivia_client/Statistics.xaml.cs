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

namespace trivia_client
{
    /// <summary>
    /// Interaction logic for Statistics.xaml
    /// </summary>
    public partial class Statistics : Page
    {
		private MenuWindow wnd;
		private Communicator _com;

		public Statistics(Communicator com, MenuWindow wnd)
		{
			try
			{
				this._com = com;
				this.wnd = wnd;
				InitializeComponent();
				StatisticsResponse response = StatisticsResponseHandler.GetStatisticsOfUser(com);
				GreetingLabel.Content += response.username;
				NumOfPlayedGamesLabel.Content += response.numPlayedGames.ToString();
				CorrectAnswerCountLabel.Content += response.correctAnswerCount.ToString();
				WrongAnswersLabel.Content += response.wrongAnswerCount.ToString();
				AverageAnswerTimeLabel.Content += response.averangeAnswerTime.ToString();
			}
			catch
			{
				wnd.ChangeToError(this.wnd);
			}
		}

		private void OnMenuClick(object sender, RoutedEventArgs e)
		{
			//Shuhman delete the username from every page, EVERY single one
			wnd.ChangeToMenu(this._com, null, wnd);
		}
		public void EndRunning(object sender, RoutedEventArgs e)
		{
			MenuResponeHandler.LogOut(this._com);
			System.Windows.Application.Current.Shutdown();
		}
	}
}
