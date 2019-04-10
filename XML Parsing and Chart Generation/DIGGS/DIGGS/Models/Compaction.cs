using System;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using System.Windows.Forms.DataVisualization.Charting;
using System.Xml;
using System.Xml.Linq;
using DIGGS.Models;
using iTextSharp.text;
using iTextSharp.text.pdf;

namespace DIGGS.Controllers
{
	public class CompactionData
	{
		public float waterContent { get; set; }
		public float dryDensity { get; set; }
	}
	public class CompactionFunctions
	{
		public List<CompactionData> ParseCompaction()
		{
			List<CompactionData> compData = new List<CompactionData>();
			XNamespace ns = "http://diggsml.org/schemas/2.0.b";
			XNamespace gns = "http://diggsml.org/schemas/2.0.b/geotechnical";
			string strAppPath = AppDomain.CurrentDomain.BaseDirectory;
			XDocument doc = XDocument.Load(strAppPath + "Content\\Compaction.xml");
			var query = doc.Root.Element(ns + "measurement").Element(ns + "Test").Element(ns + "procedure").Element(gns + "LabCompactionTest");
			var trials = query.Elements(gns + "trial").Select(x=> x.Element(gns + "LabCompactionTestTrial"));

			foreach (var item in trials)
			{
				compData.Add(new CompactionData()
				{
					waterContent = float.Parse(item.Element(gns + "waterContent").Value),
					dryDensity = float.Parse(item.Element(gns + "dryDensity").Value),
				});
			}

			return compData;
		}
		public void compChart(List<CompactionData> compData)
		{
			DataTable comp = new DataTable("Compaction Test");
			comp.Columns.Add("Dry Density", typeof(float));
			comp.Columns.Add("Moisture Content", typeof(float));

			DataRow row = comp.NewRow();
			foreach (var item in compData)
			{
				row["Dry Density"] = item.dryDensity;
				row["Moisture Content"] = item.waterContent;
				comp.Rows.Add(row);
				row = comp.NewRow();
			}
			var chart = new Chart();
			chart.Width = 900;
			chart.Height = 600;
			chart.BorderlineColor = System.Drawing.Color.White;
			chart.BorderlineDashStyle = ChartDashStyle.Solid;
			chart.BorderlineWidth = 1;
			chart.DataSource = comp;


			var area = new ChartArea("Area");
			area.BackColor = System.Drawing.Color.White;

			area.AxisY.Title = "Dry Density [kg/m3]";
			area.AxisY.Minimum = Math.Round(compData.Min(m=> m.dryDensity - 25) / 100d) * 100;
			area.AxisY.Maximum = Math.Round(compData.Max(m => m.dryDensity + 26) * 4, MidpointRounding.ToEven) / 4;
			area.AxisY.Interval = 25;
			//area.AxisY.IsReversed = true;

			area.AxisX.Minimum = Math.Round(compData.Min(m=> m.waterContent - 2));
			area.AxisX.Maximum = Math.Round(compData.Max(m => m.waterContent + 2));
			area.AxisX.Title = "Moisture Content [%]";
			area.AxisX.Interval = 1;


			chart.ChartAreas.Add(area);

			var series1 = new Series("Data");
			series1.XValueMember = "Moisture Content";
			series1.YValueMembers = "Dry Density";
			series1.MarkerStyle = MarkerStyle.Circle;
			series1.MarkerSize = 8;
			series1.ChartType = SeriesChartType.Spline;
			series1.BorderWidth = 2;
			series1.Color = System.Drawing.Color.CornflowerBlue;

			//chart.ChartAreas[0].AxisY.LabelStyle.Angle = 0;
			chart.Series.Add(series1);

			chart.DataBind();

			chart.SaveImage(@"C:\Users\Public\CompChart.png", ChartImageFormat.Png);
		}
		public MemoryStream BuildCompPDF(List<CompactionData> compData)
		{
			SimpleEventHelper _pageEventHandler = new SimpleEventHelper();
			Document doc = new Document(new Rectangle(288f, 144f), 10, 10, 10, 10);
			doc.SetPageSize(iTextSharp.text.PageSize.A4.Rotate());
			MemoryStream stream = new MemoryStream();
			var writer = PdfWriter.GetInstance(doc, stream);
			writer.CloseStream = false;
			writer.PageEvent = _pageEventHandler;
			doc.Open();

			Font titleFont = FontFactory.GetFont("Arial", 14);
			Paragraph title;
			title = new Paragraph("Compaction Test", titleFont);
			title.Alignment = Element.ALIGN_CENTER;
			doc.Add(title);

			Image compChart = Image.GetInstance(@"C:\Users\Public\CompChart.png");
			compChart.ScaleAbsolute(750, 460);
			compChart.SetAbsolutePosition(30, doc.PageSize.Height - 525);
			doc.Add(compChart);


			doc.Close();

			byte[] byteInfo = stream.ToArray();
			stream.Write(byteInfo, 0, byteInfo.Length);
			stream.Position = 0;

			return stream;
		}
	}
}