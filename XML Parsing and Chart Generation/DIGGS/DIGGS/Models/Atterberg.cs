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
    public class AtterbergData
    {
        public List<LiquidLimit> liquidList = new List<LiquidLimit>();
        public List<PlasticLimit> plasticList = new List<PlasticLimit>();
        public FirstNode firstNode = new FirstNode();
        public LastNode lastNode = new LastNode();
        public float liquidBlowCount { get; set; }
        public float liquidWaterContent { get; set; }
        public float pLimit { get; set; }
        public float minWaterContent { get; set; }
        public float maxWaterContent { get; set; }
        public class LiquidLimit
        {
            public int trialNumber { get; set; }
            public float blowCount { get; set; }
            public float waterContent { get; set; }

        }
        public class PlasticLimit
        {
            public int trialNumber { get; set; }
            public float waterContent { get; set; }
        }
        public class FirstNode
        {
            public float x { get; set; }
            public float y { get; set; }
        }
        public class LastNode
        {
            public float x { get; set; }
            public float y { get; set; }
        }
    }
    public class AtterbergFunctions
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
        public MemoryStream BuildAtterbergPDF(AtterbergData atterberg)
        {
            var doc = new Document();
            MemoryStream stream = new MemoryStream();
            var writer = PdfWriter.GetInstance(doc, stream).CloseStream = false;
            doc.Open();

            Font titleFont = FontFactory.GetFont("Arial", 20);
            Paragraph title;
            title = new Paragraph("Atterberg Limits", titleFont);
            title.Alignment = Element.ALIGN_CENTER;
            doc.Add(title);

			Image logo = Image.GetInstance(@"C:\Users\Public\test.png");
			logo.ScaleAbsolute(528, 300);
			doc.Add(logo);

			PdfPTable lTitle = new PdfPTable(1);
            lTitle.WidthPercentage = 50;
            RowBuilder(lTitle, "Liquid Limit", PdfPCell.ALIGN_CENTER, false);
            lTitle.SpacingBefore = 20;
            doc.Add(lTitle);

            PdfPTable lData = new PdfPTable(3);
            lData.WidthPercentage = 50;

            RowBuilder(lData, "Trial No", PdfPCell.ALIGN_CENTER, true);
            RowBuilder(lData, "Blow Count", PdfPCell.ALIGN_CENTER, true);
            RowBuilder(lData, "Water Content", PdfPCell.ALIGN_CENTER, true);

            foreach (var item in atterberg.liquidList)
            {
                RowBuilder(lData, item.trialNumber.ToString(), PdfPCell.ALIGN_CENTER, false);
                RowBuilder(lData, item.blowCount.ToString(), PdfPCell.ALIGN_CENTER, false);
                RowBuilder(lData, item.waterContent.ToString(), PdfPCell.ALIGN_CENTER, false);
            }

            RowBuilder(lData, "Liquid Limit", PdfPCell.ALIGN_CENTER, true);
            RowBuilder(lData, atterberg.liquidBlowCount.ToString(), PdfPCell.ALIGN_CENTER, false);
            RowBuilder(lData, atterberg.liquidWaterContent.ToString(), PdfPCell.ALIGN_CENTER, false);
            doc.Add(lData);

            PdfPTable pTitle = new PdfPTable(1);
            pTitle.WidthPercentage = 50;
            RowBuilder(pTitle, "Plastic Limit", PdfPCell.ALIGN_CENTER, false);
            doc.Add(pTitle);

            PdfPTable pData = new PdfPTable(2);
            pData.WidthPercentage = 50;

            RowBuilder(pData, "Trial No", PdfPCell.ALIGN_CENTER, true);
            RowBuilder(pData, "Water Content", PdfPCell.ALIGN_CENTER, true);

            foreach (var item in atterberg.plasticList)
            {
                RowBuilder(pData, item.trialNumber.ToString(), PdfPCell.ALIGN_CENTER, false);
                RowBuilder(pData, item.waterContent.ToString(), PdfPCell.ALIGN_CENTER, false);
            }

            RowBuilder(pData, "Plastic Limit", PdfPCell.ALIGN_CENTER, true);
            RowBuilder(pData, atterberg.pLimit.ToString(), PdfPCell.ALIGN_CENTER, false);

            doc.Add(pData);

            doc.Close();

            byte[] byteInfo = stream.ToArray();
            stream.Write(byteInfo, 0, byteInfo.Length);
            stream.Position = 0;

            return stream;
        }
        public AtterbergData ParseAtterberg()
        {
            
            AtterbergData atterberg = new AtterbergData();
            XNamespace ns = "http://diggsml.org/schemas/2.0.b";
            XNamespace gns = "http://diggsml.org/schemas/2.0.b/geotechnical";
            string strAppPath = AppDomain.CurrentDomain.BaseDirectory;
            XDocument doc = XDocument.Load(strAppPath + "Content\\digg.xml");

            var query = doc.Root.Element(ns + "measurement").Element(ns + "Test").Element(ns + "procedure").Element(gns + "AtterbergLimitsTest");
            var cas = query.Elements(gns + "casagrandeTrial").Select(c => c.Element(gns + "CasagrandeTrial"));
            var plastic = query.Elements(gns + "plasticLimitTrial").Select(c => c.Element(gns + "PlasticLimitTrial"));

            foreach (var item in cas)
            {
                atterberg.liquidList.Add(new AtterbergData.LiquidLimit()
                {
                    trialNumber = int.Parse(item.Element(gns + "trialNo").Value),
                    blowCount = float.Parse(item.Element(gns + "blowCount").Value),
                    waterContent = float.Parse(item.Element(gns + "waterContent").Value)
                });
            }

            float pLimit = 0f;
            foreach (var item in plastic)
            {
                atterberg.plasticList.Add(new AtterbergData.PlasticLimit()
                {
                    trialNumber = int.Parse(item.Element(gns + "trialNo").Value),
                    waterContent = float.Parse(item.Element(gns + "waterContent").Value)
                });
                //Suming Plastic Limit
                pLimit += float.Parse(item.Element(gns + "waterContent").Value);
            }

            //Determining regression nodes & min/max water content
            atterberg.minWaterContent = atterberg.liquidList.Min(l => l.waterContent);
            atterberg.maxWaterContent = atterberg.liquidList.Max(l => l.waterContent);
            var minBlow = atterberg.liquidList.Aggregate((m, x) => x.blowCount < m.blowCount ? x : m);
            var maxBlow = atterberg.liquidList.Aggregate((m, x) => x.blowCount > m.blowCount ? x : m);

            atterberg.firstNode.x = minBlow.blowCount;
            atterberg.firstNode.y = minBlow.waterContent;

            atterberg.lastNode.x = maxBlow.blowCount;
            atterberg.lastNode.y = maxBlow.waterContent;

            //Calculating liquid limitss
            atterberg.liquidBlowCount = 25;
            atterberg.liquidWaterContent = (-2.4297f * 25f) + 126.6f;

            //Calculating Plastic Limit
            pLimit = pLimit / atterberg.plasticList.Count();
            atterberg.pLimit = pLimit;

            return atterberg;
        }
        public void MakeChart(AtterbergData atterberg)
        {
            DataTable counts = new DataTable("LiquidLimit");
            counts.Columns.Add("BlowCount", typeof(float));
            counts.Columns.Add("WaterContent", typeof(float));
            counts.Columns.Add("FinalBlow", typeof(float));
            counts.Columns.Add("FinalCount", typeof(float));

            DataRow row = counts.NewRow();
            foreach (var item in atterberg.liquidList)
            {
                row["BlowCount"] = item.blowCount;
                row["WaterContent"] = item.waterContent;
                counts.Rows.Add(row);
                row = counts.NewRow();
            }

            row["FinalBlow"] = 25;
            row["FinalCount"] = atterberg.liquidWaterContent;
            counts.Rows.Add(row);

            var chart = new Chart();
            chart.Width = 700;
            chart.Height = 500;
            chart.BorderlineColor = System.Drawing.Color.Black;
            chart.BorderlineDashStyle = ChartDashStyle.Solid;
            chart.BorderlineWidth = 1;
            chart.BackColor = System.Drawing.Color.White;

            chart.Titles.Add(new Title("Atterberg Visualization"));
            chart.DataSource = counts;

            var area = new ChartArea("Area");
            area.BackColor = System.Drawing.Color.WhiteSmoke;
            area.BackSecondaryColor = System.Drawing.Color.White;
            area.BackGradientStyle = GradientStyle.TopBottom;

            area.AxisX.Title = "Blow Count";
            area.AxisX.Minimum = Math.Round(atterberg.firstNode.x - 5);
            area.AxisX.Maximum = Math.Round(atterberg.lastNode.x + 5);
            area.AxisX.Interval = 5;

            area.AxisY.Minimum = Math.Round(atterberg.minWaterContent - 5);
            area.AxisY.Maximum = Math.Round(atterberg.maxWaterContent + 5);
            area.AxisY.Title = "Water Content";
            area.AxisY.Interval = 10;
            area.AxisY.IsLabelAutoFit = false;

            chart.ChartAreas.Add(area);

            var series1 = new Series("Data");
            series1.XValueMember = "BlowCount";
            series1.YValueMembers = "WaterContent";
            series1.MarkerStyle = MarkerStyle.Circle;
            series1.MarkerSize = 10;
            series1.ChartType = SeriesChartType.Point;
            series1.BorderWidth = 3;
            series1.Color = System.Drawing.Color.Blue;
            chart.Series.Add(series1);

            var series2 = new Series("Liquid Limit");
            series2.XValueMember = "FinalBlow";
            series2.YValueMembers = "FinalCount";
            series2.MarkerStyle = MarkerStyle.Circle;
            series2.MarkerSize = 10;
            series2.ChartType = SeriesChartType.Point;
            series2.BorderWidth = 3;
            series2.Color = System.Drawing.Color.Orange;
            chart.Series.Add(series2);

            var series3 = new Series("Regression Line");
            series3.Points.Add(new DataPoint(atterberg.firstNode.x, atterberg.firstNode.y));
            series3.Points.Add(new DataPoint(atterberg.lastNode.x, atterberg.lastNode.y));
            series3.ChartType = SeriesChartType.Line;
            series3.BorderDashStyle = ChartDashStyle.Dot;
            series3.BorderWidth = 2;
            series3.Color = System.Drawing.Color.Blue;
            chart.Series.Add(series3);

            var legend = new Legend();
            legend.Enabled = true;
            legend.Docking = Docking.Bottom;
            legend.Alignment = System.Drawing.StringAlignment.Center;
            legend.BorderWidth = 1;
            legend.BorderDashStyle = ChartDashStyle.Solid;
            legend.BorderColor = System.Drawing.Color.Black;
            legend.ShadowColor = System.Drawing.Color.White;
            legend.ShadowOffset = 1;
            chart.Legends.Add(legend);

            chart.DataBind();

            chart.SaveImage(@"C:\Users\Public\Atter.png", ChartImageFormat.Png);
        }
    }
}