using System;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using System.Windows.Forms.DataVisualization.Charting;
using System.Xml.Linq;
using iTextSharp.text;
using iTextSharp.text.pdf;

namespace DIGGS.Models
{
    public class CPTData
    {
        public float location { get; set; }
        public float tipResist { get; set; }
        public float sleeveFriction { get; set; }
        public float porePressure { get; set; }
    }
    public class SimpleEventHelper : PdfPageEventHelper
    {
        public PdfPCell getCell(String text, int alignment)
        {
            Font smallFont = new Font(Font.FontFamily.TIMES_ROMAN, 10, Font.NORMAL);
            PdfPCell cell = new PdfPCell(new Phrase(text, smallFont));
            cell.PaddingBottom = 5;
            cell.HorizontalAlignment = alignment;

            return cell;
        }
        public void RowBuilder(PdfPTable lData, string text, int align, Boolean header)
        {
            PdfPCell row = getCell(text, align);
            if (header)
            {
                row.BackgroundColor = BaseColor.GRAY;
            }
            lData.AddCell(row);
        }
        public override void OnStartPage(PdfWriter writer, Document pdfDoc)
        {
            base.OnStartPage(writer, pdfDoc);
            if (pdfDoc.PageNumber > 1)
            {
                Image tipChart = Image.GetInstance(@"C:\Users\Public\CPTTip.png");
                tipChart.ScaleToFit(300, 150);
                tipChart.SetAbsolutePosition(0, pdfDoc.PageSize.Height - 225);
                pdfDoc.Add(tipChart);

                Image sleeveChart = Image.GetInstance(@"C:\Users\Public\CPTSleeve.png");
                sleeveChart.ScaleToFit(300, 150);
                sleeveChart.SetAbsolutePosition(0, pdfDoc.PageSize.Height - 375);
                pdfDoc.Add(sleeveChart);

                Image poreChart = Image.GetInstance(@"C:\Users\Public\CPTPore.png");
                poreChart.ScaleToFit(300, 150);
                poreChart.SetAbsolutePosition(0, pdfDoc.PageSize.Height - 525);
                pdfDoc.Add(poreChart);
                
                PdfPTable lTitle = new PdfPTable(4);
                PdfContentByte pcb = writer.DirectContent;
                lTitle.WidthPercentage = 39;
                lTitle.HorizontalAlignment = 2;
                lTitle.SpacingBefore = 5;
                RowBuilder(lTitle, "Location", PdfPCell.ALIGN_CENTER, true);
                RowBuilder(lTitle, "Tip Resistance", PdfPCell.ALIGN_CENTER, true);
                RowBuilder(lTitle, "Sleeve Friction", PdfPCell.ALIGN_CENTER, true);
                RowBuilder(lTitle, "Pore Pressure", PdfPCell.ALIGN_CENTER, true);

                pdfDoc.Add(lTitle);
            }
        }
    }
   
    public class CPTFunctions
    {
        public MemoryStream BuildCPTPDF(List<CPTData> cptData)
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
            title = new Paragraph("CPT Visualization", titleFont);
            title.Alignment = Element.ALIGN_CENTER;
            doc.Add(title);

            Image tipChart = Image.GetInstance(@"C:\Users\Public\CPTTip.png");
            tipChart.ScaleAbsolute(250, 460);
            tipChart.SetAbsolutePosition(30, doc.PageSize.Height - 525);
            doc.Add(tipChart);

            Image sleeveChart = Image.GetInstance(@"C:\Users\Public\CPTSleeve.png");
            sleeveChart.ScaleToFit(250, 460);
            sleeveChart.SetAbsolutePosition(290, doc.PageSize.Height - 525);
            doc.Add(sleeveChart);

            Image poreChart = Image.GetInstance(@"C:\Users\Public\CPTPore.png");
            poreChart.ScaleToFit(250, 460);
            poreChart.SetAbsolutePosition(550, doc.PageSize.Height - 525);
            doc.Add(poreChart);

            //PdfPTable lTitle = new PdfPTable(4);
            //PdfContentByte pcb = writer.DirectContent;
            //lTitle.WidthPercentage = 39;
            //lTitle.HorizontalAlignment = 2;
            //lTitle.SpacingBefore = 10;
            //_pageEventHandler.RowBuilder(lTitle, "Location", PdfPCell.ALIGN_CENTER, true);
            //_pageEventHandler.RowBuilder(lTitle, "Tip Resistance", PdfPCell.ALIGN_CENTER, true);
            //_pageEventHandler.RowBuilder(lTitle, "Sleeve Friction", PdfPCell.ALIGN_CENTER, true);
            //_pageEventHandler.RowBuilder(lTitle, "Pore Pressure", PdfPCell.ALIGN_CENTER, true);

            //foreach(var item in cptData)
            //{
            //    _pageEventHandler.RowBuilder(lTitle, item.location.ToString(), PdfPCell.ALIGN_CENTER, false);
            //    _pageEventHandler.RowBuilder(lTitle, item.tipResist.ToString(), PdfPCell.ALIGN_CENTER, false);
            //    _pageEventHandler.RowBuilder(lTitle, item.sleeveFriction.ToString(), PdfPCell.ALIGN_CENTER, false);
            //    _pageEventHandler.RowBuilder(lTitle, item.porePressure.ToString(), PdfPCell.ALIGN_CENTER, false);
            //}
            //doc.Add(lTitle);

            doc.Close();

            byte[] byteInfo = stream.ToArray();
            stream.Write(byteInfo, 0, byteInfo.Length);
            stream.Position = 0;

            return stream;
        }
        public List<CPTData> ParseCPT()
        {
            List<CPTData> cptData = new List<CPTData>();
            XNamespace ns = "http://diggsml.org/schemas/2.0.b";
            XNamespace gns = "http://www.opengis.net/gml/3.2";
            string strAppPath = AppDomain.CurrentDomain.BaseDirectory;
            XDocument doc = XDocument.Load(strAppPath + "Content\\CPT.xml");
            var query = doc.Root.Element(ns + "measurement").Element(ns + "Test").Element(ns + "outcome").Element(ns + "TestResult");
            var location = query.Element(ns + "location").Element(ns + "MultiPointLocation").Element(gns + "posList");
            var dataValues = query.Element(ns + "results").Element(ns + "ResultSet").Element(ns + "dataValues");

            var locs = location.Value
                .Split('\n')
                .Where(f => !string.IsNullOrWhiteSpace(f))
                .Select(f => float.Parse(f))
                .ToArray();

            var values = dataValues.Value
                .Split('\n')
                .Where(f => !string.IsNullOrWhiteSpace(f))
                .Select(f => f
                    .Split(',')
                    .Select(a => float.Parse(a))
                    .ToArray()
                ).ToArray();

            for (int i = 0; i < locs.Count(); i++)
            {
                cptData.Add(new CPTData()
                {
                    location = locs[i],
                    tipResist = values[i][0],
                    sleeveFriction = values[i][1],
                    porePressure = values[i][2]
                });
            }

            return cptData;
        }
        public void TipChart(List<CPTData> cptData)
        {
            DataTable tips = new DataTable("Tip Resistance");
            tips.Columns.Add("Depth", typeof(float));
            tips.Columns.Add("Resistance", typeof(float));

            DataRow row = tips.NewRow();
            foreach (var item in cptData)
            {
                row["Depth"] = item.location;
                row["Resistance"] = item.tipResist;
                tips.Rows.Add(row);
                row = tips.NewRow();
            }
            var chart = new Chart();
            chart.Width = 400;
            chart.Height = 600;
            chart.BorderlineColor = System.Drawing.Color.White;
            chart.BorderlineDashStyle = ChartDashStyle.Solid;
            chart.BorderlineWidth = 1;
            chart.DataSource = tips;


            var area = new ChartArea("Area");
            area.BackColor = System.Drawing.Color.White;
            area.BackSecondaryColor = System.Drawing.Color.LightGray;
            area.BackGradientStyle = GradientStyle.TopBottom;

            area.AxisY.Title = "Depth (m)";
            area.AxisY.Minimum = 0;
            area.AxisY.Maximum = 16;
            area.AxisY.Interval = 2;
            area.AxisY.IsReversed = true;
          
            area.AxisX.Minimum = 0;
            area.AxisX.Maximum = 100;
            area.AxisX.Title = "Tip Resistance (kN/m2)";
            area.AxisX.Interval = 50;
            

            chart.ChartAreas.Add(area);

            var series1 = new Series("Data");
            series1.XValueMember = "Resistance";
            series1.YValueMembers = "Depth";
            series1.MarkerStyle = MarkerStyle.Circle;
            series1.MarkerSize = 5;
            series1.ChartType = SeriesChartType.Point;
            series1.BorderWidth = 3;
            series1.Color = System.Drawing.Color.ForestGreen;

            chart.ChartAreas[0].AxisY.LabelStyle.Angle = 0;
            chart.Series.Add(series1);

            chart.DataBind();

            chart.SaveImage(@"C:\Users\Public\CPTTip.png", ChartImageFormat.Png);
        }
        public void SleeveChart(List<CPTData> cptData)
        {
            DataTable tips = new DataTable("Sleeve Friction");
            tips.Columns.Add("Depth", typeof(float));
            tips.Columns.Add("Friction", typeof(float));

            DataRow row = tips.NewRow();
            foreach (var item in cptData)
            {
                row["Depth"] = item.location;
                row["Friction"] = item.sleeveFriction;
                tips.Rows.Add(row);
                row = tips.NewRow();
            }
            var chart = new Chart();
            chart.Width = 300;
            chart.Height = 600;
            chart.BorderlineColor = System.Drawing.Color.White;
            chart.BorderlineDashStyle = ChartDashStyle.Solid;
            chart.BorderlineWidth = 1;
            chart.DataSource = tips;


            var area = new ChartArea("Area");
            area.BackColor = System.Drawing.Color.White;
            area.BackSecondaryColor = System.Drawing.Color.LightGray;
            area.BackGradientStyle = GradientStyle.TopBottom;

            area.AxisY.Title = "Depth (m)";
            area.AxisY.Minimum = 0;
            area.AxisY.Maximum = 16;
            area.AxisY.Interval = 2;
            area.AxisY.IsReversed = true;
          
            area.AxisX.Minimum = 0;
            area.AxisX.Maximum = 3;
            area.AxisX.Title = "Sleeve Friction (kN/m2)";
            area.AxisX.Interval = 1;

            chart.ChartAreas.Add(area);

            var series1 = new Series("Data");
            series1.XValueMember = "Friction";
            series1.YValueMembers = "Depth";
            series1.MarkerStyle = MarkerStyle.Circle;
            series1.MarkerSize = 5;
            series1.ChartType = SeriesChartType.Point;
            series1.BorderWidth = 3;
            series1.Color = System.Drawing.Color.OrangeRed;

            chart.Series.Add(series1);
            chart.ChartAreas[0].AxisY.LabelStyle.Angle = 0;
            chart.DataBind();

            chart.SaveImage(@"C:\Users\Public\CPTSleeve.png", ChartImageFormat.Png);
        }
        public void PoreChart(List<CPTData> cptData)
        {
            DataTable tips = new DataTable("Pore Pressure");
            tips.Columns.Add("Depth", typeof(float));
            tips.Columns.Add("Pressure", typeof(float));

            DataRow row = tips.NewRow();
            foreach (var item in cptData)
            {
                row["Depth"] = item.location;
                row["Pressure"] = item.sleeveFriction;
                tips.Rows.Add(row);
                row = tips.NewRow();
            }
            var chart = new Chart();
            chart.Width = 300;
            chart.Height = 600;
            chart.BorderlineColor = System.Drawing.Color.White;
            chart.BorderlineDashStyle = ChartDashStyle.Solid;
            chart.BorderlineWidth = 1;
            chart.DataSource = tips;


            var area = new ChartArea("Area");
            area.BackColor = System.Drawing.Color.White;
            area.BackSecondaryColor = System.Drawing.Color.LightGray;
            area.BackGradientStyle = GradientStyle.TopBottom;
            area.AxisY.Title = "Depth (m)";
            area.AxisY.Minimum = 0;
            area.AxisY.Maximum = 16;
            area.AxisY.Interval = 2;
            area.AxisY.IsReversed = true;
          
            area.AxisX.Minimum = -.5;
            area.AxisX.Maximum = 3.5;
            area.AxisX.Title = "Pore Pressure (kN/m2)";
            area.AxisX.Interval = .5;

            chart.ChartAreas.Add(area);

            var series1 = new Series("Data");
            series1.XValueMember = "Pressure";
            series1.YValueMembers = "Depth";
            series1.MarkerStyle = MarkerStyle.Circle;
            series1.MarkerSize = 5;
            series1.ChartType = SeriesChartType.Point;
            series1.BorderWidth = 3;
            series1.Color = System.Drawing.Color.Blue;

            chart.ChartAreas[0].AxisY.LabelStyle.Angle = 0;
            chart.Series.Add(series1);

            chart.DataBind();

            chart.SaveImage(@"C:\Users\Public\CPTPore.png", ChartImageFormat.Png);
        }
    }
}