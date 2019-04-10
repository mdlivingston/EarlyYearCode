using System.Collections.Generic;
using System.IO;
using System.Web.Mvc;
using DIGGS.Models;

namespace DIGGS.Controllers
{
   
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            return View();
        }
        
        public ActionResult About()
        {
            ViewBag.Message = "Your application description page.";

            return View();
        }

        public ActionResult Contact()
        {
            ViewBag.Message = "Your contact page.";

            return View();
        }
       
        public ActionResult ConstructAtterberg()
        {
            AtterbergFunctions atterFunc = new AtterbergFunctions();
            AtterbergData atterberg = atterFunc.ParseAtterberg();
            atterFunc.MakeChart(atterberg);
            MemoryStream stream = atterFunc.BuildAtterbergPDF(atterberg);
            return File(stream, "application/pdf");

        }
        public ActionResult ConstructCPT()
        {
            CPTFunctions cptFunc = new CPTFunctions();
            List<CPTData> cptData = cptFunc.ParseCPT();
            cptFunc.TipChart(cptData);
            cptFunc.SleeveChart(cptData);
            cptFunc.PoreChart(cptData);
            MemoryStream stream = cptFunc.BuildCPTPDF(cptData);
            return File(stream, "application/pdf");

        }

		public ActionResult ConstructCompaction()
		{
			CompactionFunctions compFunc = new CompactionFunctions();
			List<CompactionData> compData = compFunc.ParseCompaction();
			compFunc.compChart(compData);
			MemoryStream stream = compFunc.BuildCompPDF(compData);
			return File(stream, "application/pdf");
		}

    }
}