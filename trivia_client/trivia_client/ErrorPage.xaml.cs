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
    /// Interaction logic for ErrorPage.xaml
    /// </summary>
    public partial class ErrorPage : Page
    {
		private MenuWindow wnd;

		public ErrorPage(MenuWindow wnd)
		{
			InitializeComponent();
			this.wnd = wnd;
		}

		private void ReturnToLogin(object sender, RoutedEventArgs e)
		{
			wnd.Hide();
			MainWindow newWnd = new MainWindow();
			newWnd.Show();
		}

		public void EndRunning(object sender, RoutedEventArgs e)
		{
			System.Windows.Application.Current.Shutdown();
		}
	}
}
