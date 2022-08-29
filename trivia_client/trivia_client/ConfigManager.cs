using System;
using System.Collections.Generic;
using System.Text;

namespace trivia_client
{
    class ConfigManager
    {
        private static string[] getConfigContent()
        {
            try
            {
                string[] data = System.IO.File.ReadAllLines("config.txt");
                if (data.Length < 2)
                    throw new Exception("Config Not Right");
                return data;
            }
            catch
            {
                throw new Exception("Cant Find Config.txt");
            }

        }

        public static string getConfigIP()
        {
            string ip = getConfigContent()[0];
            if (!ip.Contains("-") && ip.Split("-").Length < 2)
                throw new Exception("Config Not Right");
            return ip.Split("-")[1];
        }

        public static int getConfigPort()
        {
            string port = getConfigContent()[1];
            if (!port.Contains("-") && port.Split("-").Length < 2 && !int.TryParse(port.Split("-")[1], out _))
                throw new Exception("Config Not Right");
            return Int32.Parse(port.Split("-")[1]);
        }
    }
}
