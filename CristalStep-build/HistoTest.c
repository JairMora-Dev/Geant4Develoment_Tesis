


void HistoTest()
{
    //Crear un canvas con nombre c1 de tamaño 900 x 700
    TCanvas *c1 = new TCanvas("c1","multipads",900,700);
    
    
    //Dividir el Canvas en dos columnas y una fila:
    //columnas y filas
    //c1->Divide(3,1);


    //Crear histograma en 1-D con nombre hist1 y rótulo h1; el histograma
    //consiste de 100 bins entre 0 y 100
    TH1D* hist1 = new TH1D("eDep_proton","Energia Depositada",100,0,1.5);
    //TH1D* hist2 = new TH1D("Track_proton","Track Length",100,1,100);
    //TH1D* hist3 = new TH1D("Dosis_proton","Dosis Depositada",100,-0.00000001,0.0000003);
    //TH1D* hist4 = new TH1D("Flux_proton","Flujo",40,-200,900);
    //TH2D* hist0 = new TH2D("eDep_vs_Profundidad","Energia depositada vs Profundidad",50, 0, 1.5, 50,0,400);
    


    //Abrir el archivo que contiene los datos de entrada. El archivo contiene 5 columnas  con 100 filas
    //La tres primeras columnas correponden a variables tipo int ( x, y, z,)
    //La cuarta columna contiene variables tipo double ( Edep (Mev))
    
    ifstream inp1;
    inp1.open("Energiadepositada1.txt");

    //Declaración de variables
    int a, b, c, e;
    double d;
    double factor = 300.0/300;
    
    double k= 0.00127;
    double ki= 0.000635;
    
    //////////////Histograma Energia depositada////////////
    while (inp1 >> a >> b >> c >> d >> e)
    {
        hist1->Fill(((c*k)+ki)*factor,d);
        //hist0->Fill(((c*k)+ki),d);
    }
    
    ////////////Histograma del Track////////////////
    
    ifstream inp2;
    inp2.open("TrackL.txt");
    
    
    while (inp2 >> a >> b >> c >> d >> e)
    {
        //hist2->Fill(d);
        //hist0->Fill(c,d);
    }
    
    ///////////Histograma Dosis Depositada //////////
    
    ifstream inp3;
    inp3.open("Dosis_depositada.txt");
    
    while (inp3 >> a >> b >> c >> d >> e)
    {
        //hist3->Fill(d);
        //hist0->Fill(c,d);
    }
    
    ifstream inp4;
    inp4.open("CFlujo.txt");
    
    while (inp4 >> a >> b >> c >> d >> e)
    {
        //hist4->Fill(d);
        //hist0->Fill(c,d);
    }
    
    
    
    
    //Acceder a cada uno de los subpaneles del Canvas c1
    ////////////////////////////////Draw_Edep//////////////
    c1->cd(1);
    hist1->Draw("hist1");
    hist1->Draw();
    Double_t scale = hist1->GetMaximum();
    hist1->Scale(1.0/scale);
    hist1->Draw("SAME");
    ////////////////////////////////Draw_Track////////////
    //c1->cd(1);
    //hist2->Draw("hist2");
    ////////////////////////////////Draw_Dosis/////////////
    //c1->cd(1);
    //hist3->Draw("hist3");
    /////////////////////////////// Draw_Flux//////////////
    //c1->cd(1);
    //hist4->Draw("hist4");
    
    
    //////////////////////////Edep_vs_Profundidad//////////
    //c1->cd(1);
    //hist0->Draw("hist0");
    //hist0->Draw("CONT0 COLZ");
    
    
    //Cerrar archivo de entrada de datos
    inp1.close();
}
