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
    /// Interaction logic for MenuPage.xaml
    /// </summary>
    public partial class MenuPage : Page
    {
        MenuWindow wnd;
        private Communicator _com;
        private string username;

        public MenuPage(Communicator com, string username, MenuWindow wnd)
        {
            InitializeComponent();
            this.wnd = wnd;
            this._com = com;
            this.username = username;
        }
        private void OnCreateRoomClick(object sender, RoutedEventArgs e)
        {
            try
            {
                if (RoomNameBox.Text == "")
                {
                    MessageLabelCreate.Content = "Please enter room name";
                    return;
                }

                CreateRoomRequest createRoomRequest;
                createRoomRequest.roomName = RoomNameBox.Text;
                createRoomRequest.difficulty = this.DifficultyBox.Text;
                createRoomRequest.answerTimeOut = uint.Parse(TimerBox.Text);
                createRoomRequest.maxUsers = uint.Parse(MaxPlayersBox.Text);
                createRoomRequest.questionCount = uint.Parse(NumberOfQuestionsBox.Text);

                CreateRoomResponse response = MenuResponeHandler.CreateRoom(this._com, createRoomRequest);

                if (response.status == Constants.Success)
                    wnd.ChangeToLobby(true, this.username, response.roomId.ToString(), RoomNameBox.Text, createRoomRequest.answerTimeOut.ToString(), createRoomRequest.difficulty, createRoomRequest.questionCount.ToString(), this._com, wnd);
                else
                    MessageLabelCreate.Content = "Couldn't create room, please try again later";

            }
            catch
            {
                wnd.ChangeToError(wnd);
            }
        }

        private void OnJoinRoomClick(object sender, RoutedEventArgs e)
        {
            try
            {
                if (RoomIdBox.Text == "")
                {
                    MessageLabelJoin.Content = "Please Enter ID";
                    return;
                }
                else if (!Microsoft.VisualBasic.Information.IsNumeric(RoomIdBox.Text))
                {
                    MessageLabelJoin.Content = "Room ID Must be number";
                    return;
                }
                JoinRoomRequest request;
                request.roomId = Convert.ToUInt32(RoomIdBox.Text);

                JoinRoomResponse response = MenuResponeHandler.JoinRoom(this._com, request);
                if (response.status == Constants.Success)
                    wnd.ChangeToLobby(false, this.username, response.roomId.ToString(), response.roomName, response.answerTimeOut.ToString(), response.difficulty, response.questionCount.ToString(), this._com, wnd);
                else
                    MessageLabelJoin.Content = "Invalid room id";
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
                MenuResponeHandler.LogOut(this._com);
                System.Windows.Application.Current.Shutdown();
            }
            catch
            {
                System.Windows.Application.Current.Shutdown();
            }
        }

        private void OnProfileClick(object sender, RoutedEventArgs e)
        {
            wnd.ChangeToStatistics(this._com, wnd);
        }
    }
}
