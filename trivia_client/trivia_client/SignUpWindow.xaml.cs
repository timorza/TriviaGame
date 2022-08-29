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
    /// Interaction logic for SignUpWindow.xaml
    /// </summary>
    public partial class SignUpWindow : Window
    {
        private Communicator _com;

        public SignUpWindow(Communicator com)
        {
            InitializeComponent();
            this._com = com;
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
        public string CheckSignUpContent(string password, string confirmPassword)
        {
            if (password != confirmPassword)
                return "Password's Are not Matching!";

            return null;
        }

        private void Signup_Button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                string signupCheck = CheckSignUpContent(PasswordBox.Password, RePasswordBox.Password);
                if (signupCheck != null)
                    MessageLabelSignup.Content = signupCheck;
                else
                {
                    SignupRequest request = new SignupRequest(UsernameBox.Text, PasswordBox.Password, EmailBox.Text);
                    //Sign up was a success
                    string responeMsg = LoginResponeHandler.CheckSignUp(this._com, request);
                    if (responeMsg == null)
                    {
                        this.Hide();
                        MenuWindow wnd = new MenuWindow(this._com, UsernameBox.Text);
                        wnd.ShowDialog();
                    }
                    else
                        MessageLabelSignup.Content = responeMsg;
                }
            }
            catch
            {
                MessageLabelSignup.Content = "Can't reach server, returning in 5 seconds to login";
                System.Threading.Thread.Sleep(5000);
                this.Visibility = Visibility.Collapsed;
                MainWindow wnd = new MainWindow();
                wnd.ShowDialog();
            }
        }
    }
}
