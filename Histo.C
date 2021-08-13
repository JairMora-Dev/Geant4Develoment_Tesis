

void Histo() 
{	
  //Crear un canvas con nombre c1 de tamaño 900 x 700
  TCanvas *c1 = new TCanvas("c1","multipads",900,700);
  
  c1->Divide(2,2);
  gStyle->SetOptStat(kTRUE);
 
  //Crear histograma en 1-D con nombre hist1 y rótulo h1; el histograma
  TH1D* hist1E = new TH1D("EDepos","Energia Depositada;Edep (keV);Eventos",300,0,300);
  //TH1D* hist1E = new TH1D("EDepos","Energía Depositada;Edep;Eventos",500,0,500);
  //TH1D* hist1E = new TH1D("EDepos","Energía Depositada;Edep;Eventos",1000,0,1000);
  
  TH1D* hist1D = new TH1D("EDepos2","Energía Depositada;Ddep;Eventos",6000,0,300);
  //TH1D* hist1D = new TH1D("DDepos","Dosis Depositada;Ddep;Eventos",500,0,500);
  //TH1D* hist1D = new TH1D("DDepos","Dosis Depositada;Ddep;Eventos",1000,0,1000);
  //TH2D* hist2D = new TH2D("DDepos2","Dosis Depositada;Ddep;Eventos",300,0,300, 100, 0, 0.12);

  TH1D* hist1C = new TH1D("EDepos3","Energía Depositada;Ddep;Eventos",6000,0,300);

  TH1D* hist1B = new TH1D("EDepos4","Energía Depositada;Ddep;Eventos",300,0,300);
  
  ifstream inp, inp2, inp3, inp4;
  inp.open("eDep.txt");
  inp2.open("DatosG4ValidationQBBC.dat");
  inp3.open("DatosG4ValidationQGSPBICHP.dat");
  inp4.open("LET_All_Run.dat");
  
  //Declaración de variables
  int a, b, c;
  double d, e;
  int c2, d2, g2, h2, i2, j2;
  double a2, b2, e2, f2; 
  int c3, d3, g3, h3, i3, j3;
  double a3, b3, e3, f3;
  double a4, b4, c4, d4;
 
  double factor = 300.0/300;
  
  //Energía Depositada
  while (inp >> a >> b >> c >> d >> e)
    {
      //cout << c << "  " << d << endl;
      hist1E->Fill(c*factor,d);
    }
  inp.close();
  
  //Energía Depositada QBBC Validation
  while (inp2 >> a2 >> b2 >> c2 >> d2 >> e2 >> f2 >> g2 >> h2 >> i2 >> j2)
    {
      hist1D->Fill(a2,b2);
      //hist2D->Fill(a2,b2);
    }
  inp2.close();
  
  //Energía Depositada QGSP_BIC_HP Validation
  while (inp3 >> a3 >> b3 >> c3 >> d3 >> e3 >> f3 >> g3 >> h3 >> i3 >> j3)
    {
      hist1C->Fill(a3,b3);
    }
  inp3.close();

  //Energía Depositada QGSP_BIC_HP Validation
  while (inp4 >> a4 >> b4 >> c4 >> d4)
    {
      hist1B->Fill(a4, d4);
    }
  inp4.close();
  
  //Acceder a cada uno de los seis subpaneles del Canvas c1
  c1->cd(1);
  cout << hist1E->GetMaximum() << endl;
  Double_t scale = hist1E->GetMaximum();
  hist1E->Scale(1.0/scale);
  hist1E->Draw();
  
  c1->cd(2);
  //hist1D->Draw();
  cout << hist1D->GetMaximum() << endl;
  Double_t scale2 = hist1D->GetMaximum();
  hist1D->Scale(1.0/scale2);
  hist1D->Draw();

  c1->cd(3);
  //hist1D->Draw();
  
  cout << hist1C->GetMaximum() << endl;
  Double_t scale3 = hist1C->GetMaximum();
  hist1C->Scale(1.0/scale3);
  //hist1C->Draw();
  cout << hist1B->GetMaximum() << endl;
  Double_t scale4 = hist1B->GetMaximum();
  hist1B->Scale(1.0/scale4);
  hist1B->Draw();
  hist1E->Draw("SAME");

  c1->cd(4);
  //gPad->SetLogx(1);
  //gStyle->SetOptStat(kFALSE);
  hist1E->SetMarkerColor(kRed);
  hist1E->SetMarkerStyle(20);
  hist1E->SetMarkerSize(1.0);
  //hist1E->Draw("LP");
  hist1B->Draw("LP");
  hist1D->Draw("SAME");
  //hist1C->Draw("SAME");
  
}
