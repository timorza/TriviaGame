using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
		private Communicator _com;

		public MainWindow()
        {
			InitializeComponent();
			Thread comThread = new Thread(initiateCommunication);
			comThread.Start();
		}
		private void retryCommunication(object sender, KeyEventArgs e)
		{
			if (e.Key == Key.F5 && this._com == null)
			{
				Thread comThread = new Thread(initiateCommunication);
				comThread.Start();
			}
		}
		public void initiateCommunication()
		{
			try
			{
				this._com = new Communicator();
				this.Dispatcher.Invoke(() =>
				{
					MessageLabelMain.Content = null;
				});
			}
			catch (Exception ex)
			{
				this.Dispatcher.Invoke(() =>
				{
					MessageLabelMain.Content = ex.Message + " - Press F5 to retry";
				});
				this._com = null;
			}
		}
		public void Signup_Click(object sender, RoutedEventArgs e)
		{
			App.Current.MainWindow.Hide();
			SignUpWindow wnd = new SignUpWindow(this._com);
			wnd.ShowDialog();
		}
		public void Login_Click(object sender, RoutedEventArgs e)
        {
			try
			{
				LoginRequest req;
				req.username = UsernameBox.Text;
				req.password = PasswordBox.Password;
				bool success = LoginResponeHandler.CheckLogin(this._com, req);
				if (success)
				{
					App.Current.MainWindow.Hide();
					MenuWindow wnd = new MenuWindow(this._com, req.username);
					wnd.ShowDialog();
				}
				else 
				{
					MessageLabelMain.Content = "Username or Password Incorrect";
				}
			}
			catch
			{
				this._com = null;
				MessageLabelMain.Content = "Couldn't reach server - Press F5 to retry";
			}

		}
		public void EndRunning(object sender, RoutedEventArgs e)
		{
			System.Windows.Application.Current.Shutdown();
		}
		private void Window_MouseDown(object sender, MouseButtonEventArgs e)
		{
			if (e.ChangedButton == MouseButton.Left)
				this.DragMove();
		}
	}
}
