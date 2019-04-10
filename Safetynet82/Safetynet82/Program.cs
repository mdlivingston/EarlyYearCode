using System;
using System.Collections.Generic;
using System.Net.Mail;
using RandomNameGeneratorLibrary;
using Safetynet82.Properties;

namespace Safetynet
{
	class Program
	{

		static void Main(string[] args)
		{
			
			var personGenerator = new PersonNameGenerator();

			List<string> domains = new List<string>(new string[] { "ua", "pa", "spam", "bc", "havard", "sheltonstate", "alabama", "university" });
			List<string> endings = new List<string>(new string[] { "com", "org", "us", "edu", "eu", "net", "spam", "gov" });

			Random rnd = new Random();
			int emails = rnd.Next(100, 1000);

			string text = Resources.Insane;
			var stringRipper = text.Split('\n');
			int numberRetries = 0;
			while (numberRetries <= 50)
			{
				int i = 0;
				for (i = 0; i < emails; i++)
				{
					var name = personGenerator.GenerateRandomFirstAndLastName();
					name = name.Replace(" ", ".");
					int doms = rnd.Next(0, 7);
					int ends = rnd.Next(0, 6);
					int messages = rnd.Next(3, 62);
					try
					{
						MailMessage spamMessage = new MailMessage($"{name}@{domains[doms]}.{endings[ends]}", "mskipwith@ua.edu", "The Warning Signs Of InSaNiTy", stringRipper[messages]);
						using (var client = new SmtpClient("care-web.caps.ua.edu", 25))
						{
							client.EnableSsl = true;
							client.UseDefaultCredentials = false;

							client.Send(spamMessage);
						}
					}
					catch(Exception ex)
					{
						numberRetries++;
					}
				}
				if (i == emails)
				{
					break;
				}
			}
			MailMessage MyMessage = new MailMessage("EmailSpammerResults@ua.net", "mdlivingston@ua.edu", $"{emails} emails were just spammed to you know you ;) ", "Your program hopes you have a great day!");
			using (var client = new SmtpClient("care-web.caps.ua.edu", 25))
			{
				client.EnableSsl = true;
				client.UseDefaultCredentials = false;

				client.Send(MyMessage);
			}
		}
	}
}
