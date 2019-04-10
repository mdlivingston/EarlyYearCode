using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Net.Mail;

namespace EmailSteve
{
	public class BadIPs
	{
		public string IP { get; set; }
	}
	class Program
	{
		static void Main(string[] args)
		{
			Boolean mainRip = false;
			int zeroCount = 0;
			List<BadIPs> bList = new List<BadIPs>();

			var config = ControllerSection.GetConfig();
			foreach (ControllerElement controller in config.Controllers)
			{
				var conn = new SqlConnection
				{
					ConnectionString = ConfigurationManager.ConnectionStrings["MOE"].ToString()
				};

				conn.Open();

				for (int i = 0; i < 24; i++)
				{
					var cmd = new SqlCommand
					{
						Connection = conn,
						CommandText = $"declare @Day datetime; set @Day = '" + DateTime.Now.AddDays(-1).ToShortDateString() + "'; declare @DayAfter datetime; set @DayAfter = dateadd(day, 1, @Day); declare @IPAddress varchar(15); set @IPAddress = '" + controller.IpAddress + "';" +
									 "select count(*) from Controller_Event_Log C join Signals s on C.SignalID = s.SignalID and s.IPAddress = @IPAddress  where Timestamp between @Day and @DayAfter and datepart(hour, Timestamp) = " + i,
						CommandType = CommandType.Text
					};

					cmd.CommandTimeout = 120;
					var signalId = (int)cmd.ExecuteScalar();

					if (signalId == 0)
					{
						zeroCount++;
					}
					cmd.Dispose();

				}
				if (zeroCount == 24)
				{
					mainRip = true;
					bList.Add(new BadIPs()
					{
						IP = controller.IpAddress
					});
				}
				conn.Close();
				zeroCount = 0;
			}
			string bIPS = "";
			foreach (var item in bList)
			{
				bIPS += " " + item.IP + " | ";
			}
			using (var client = new SmtpClient("smtp.ua.edu", 25))
			{
				client.EnableSsl = true;
				client.UseDefaultCredentials = false;


				MailMessage reportMessage = new MailMessage("Daily Emailer no-reply@caps.ua.edu", "mdlivingston@ua.edu", "Daily Update", "");

				if (mainRip == false)
				{
					reportMessage.Body = "Hello Steve and Max,"
						+ Environment.NewLine + Environment.NewLine +
						"All updates from " + DateTime.Now.AddDays(-1).ToShortDateString() + " look good!"
							+ Environment.NewLine + Environment.NewLine +
							"Best Regards,"
							+ Environment.NewLine + Environment.NewLine +
							"Max's Automated Messenger";
				}
				else
				{
					reportMessage.Body = "Hello Steve and Max,"
					  + Environment.NewLine + Environment.NewLine +
					  "There seems to be a problem with *" + bList.Count() + "* controller(s):" + bIPS + "from " + DateTime.Now.AddDays(-1).ToShortDateString() + "."
						  + Environment.NewLine + Environment.NewLine +
						  "Best Regards,"
						  + Environment.NewLine + Environment.NewLine +
						  "Max's Automated Messenger";
				}

				reportMessage.To.Add("steve.burdette@ua.edu ");

				client.Send(reportMessage);
			}
		}
	}
}
