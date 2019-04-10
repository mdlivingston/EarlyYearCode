using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Net.Mail;


namespace sendSMS
{
    class SendSMS
    {
        static void Main(string[] args)
        {
            using (var client = new SmtpClient("smtp.ua.edu", 25))
            {
                client.EnableSsl = true;
                client.UseDefaultCredentials = false;

                MailMessage reportMessage = new MailMessage("MySon@sms.pa.edu", "8656795561@tmomail.net", ";)", "");

                reportMessage.Body = "Hello My Son";
                
                client.Send(reportMessage);
            }
        }
    }
}