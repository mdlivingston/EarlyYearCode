using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Data.SqlClient;
using System.Configuration;
using System.Data;
namespace ChartJSGeneration.Controllers
{
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            return View();
        }
        public ActionResult About()
        {
            return View();
        }

        public List<object> SQLReader(SqlDataReader reader)
        {
            var data = new List<object>();
            if (reader.HasRows)
            {
                while (reader.Read())
                {
                    int sampleId = (int)reader["SampleID"];
                    string analyte = (string)reader["Analyte"];
                    double result;
                    if (reader["Result"] != null && reader["Result"] != DBNull.Value)
                    {
                        result = (double)reader["Result"];
                    }
                    else
                    {
                        result = 0;
                    }
                    string location = (string)reader["Location"];
                    DateTime date = (DateTime)reader["DateSampled"];
                    string flag;
                    if (reader["Flag"] != null && reader["Flag"] != DBNull.Value)
                    {
                        flag = (string)reader["Flag"];
                    }
                    else
                    {
                        flag = "";
                    }
                    string units = (string)reader["Units"];
                    data.Add(new
                    {
                        SampleId = sampleId,
                        Analyte = analyte,
                        Result = result,
                        Location = location,
                        Date = date.ToShortDateString(),
                        Flag = flag,
                        Units = units
                    });
                }
            }
            reader.Close();
            return data;
        }
        [HttpGet]
        public JsonResult GetChart(string[] Location, string DateStart, string DateEnd, string[] Analyte)
        {
            Analyte = Analyte[0].Replace("\"", "").Replace("[", "").Replace("]", "").Split(',');
            Location = Location[0].Replace("\"", "").Replace("[", "").Replace("]", "").Split(',');

            var keys = new Dictionary<string, List<object>>();
            var data = new List<object>();
            string key = "";
            string query = $"select RD.Sample_ID as SampleID, RD.Analyte as Analyte, RD.Result as Result, S.Loc_Name as Location, S.Date_Sampled as DateSampled, RD.Flag as Flag, RD.Units as Units " +
                           "from Result_Data RD " +
                           "join Samples S on S.Sample_ID = RD.Sample_ID ";

            string connectionString = ConfigurationManager.ConnectionStrings["PlumeConnection"].ConnectionString;
            var conn = new SqlConnection(connectionString);

            conn.Open();

            SqlCommand cmd = new SqlCommand();
            SqlDataReader reader;

            cmd.Connection = conn;
            cmd.CommandType = CommandType.Text;

            if (Location.Count() > 1) //Mulitple Locations
            {
                foreach (var item in Location)
                {
                    key = item;
                    cmd.CommandText = query + "where S.Loc_Name = '" + item + "' and RD.Analyte = '" + Analyte[0] + "' and  S.Date_Sampled >= '" + Convert.ToDateTime(DateStart) + "' and  S.Date_Sampled <= '" + Convert.ToDateTime(DateEnd) + "'" + "order by S.Date_Sampled asc";

                    reader = cmd.ExecuteReader();
                    data = SQLReader(reader);

                    keys.Add(key, data);
                }
            }
            else //Multiple Analytes or One of Each
            {
                foreach (var item in Analyte)
                {
                    key = item;
                    cmd.CommandText = query + "where S.Loc_Name = '" + Location[0] + "' and RD.Analyte = '" + item + "' and  S.Date_Sampled >= '" + Convert.ToDateTime(DateStart) + "' and  S.Date_Sampled <= '" + Convert.ToDateTime(DateEnd) + "'" + "order by S.Date_Sampled asc";
                   
                    reader = cmd.ExecuteReader();
                    data = SQLReader(reader);

                    keys.Add(key, data);
                }
            }
            conn.Close();

            return Json(keys, JsonRequestBehavior.AllowGet);
        }

        public ActionResult Contact()
        {
            ViewBag.Message = "Your contact page.";

            return View();
        }
    }
}