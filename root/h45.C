void h45(){
    const int num = 15;
    int n[num];
    n[0] = 57;
    n[1] = 203;
    n[2] = 383;
    n[3] = 525;
    n[4] = 532;
    n[5] = 408;
    n[6] = 273;
    n[7] = 139;
    n[8] = 45;
    n[9] = 27;
    n[10] = 10;
    n[11] = 4;
    n[12] = 0;
    n[13] = 1;
    n[14] = 1;
    //(a)
    double mean,total = 0,sigma;
    double sum = 0,sum_s = 0;
    for(int i = 0;i < num;i++)
    {
        sum += n[i] * i;
        total += n[i];
    }
    mean = sum / total;
    cout<<"total number: "<<total<<endl;
    cout<<"mean of sample: "<<mean<<endl;
    for(int i = 0;i < num;i++)
    {
        sum_s += n[i] * (i - mean) * (i - mean);
    }
    sum_s = sum_s / (total - 1);
    sigma = sqrt(sum_s);
    cout<<"sigma^2: "<<sum_s<<endl;
    cout<<"t: "<<sum_s / mean<<endl;
    
    //(b)
    double p_value = ROOT::Math::chisquared_cdf(2607*0.955,2607) + ROOT::Math::chisquared_cdf_c(2607*1.045,2607);
    cout<<"P-value of (b): "<<p_value<<endl;
    
    //(c)
    TRandom3 *rnd = new TRandom3();
    const int groups = 20000;
    TH1F *h1 = new TH1F("h1","distribution of t",50,0.85,1.15);
    TH1F *h2 = new TH1F("h2","distribution of (n_{tot}-1)t and Gaussian",50,total * 0.85,total * 1.15);
    double data;
    double mean_i,sigma_i,t_i;
    TH1F *h0 = 0;
    double count = 0;
    double dt = 1 - 0.955;
    for(int i = 0;i < groups;i++)
    {
        if(h0 != 0)
            delete h0;
        h0 = new TH1F("h0","h0",20,0,20+1e-5);
        for(int j = 0;j < total;j++)
        {
            data = rnd->Poisson(mean);
            h0->Fill(data);
        }
        mean_i = h0->GetMean();
        sigma_i = h0->GetRMS();
        t_i = sigma_i * sigma_i / mean_i;
        //if(i % 100 ==0)
            //cout<<t_i<<endl;
        h1->Fill(t_i);
        h2->Fill(t_i * (total - 1));
        if(t_i < 1 - dt || t_i > 1 + dt)
            count++;
    }
    cout<<"P-value of (c): "<<count / groups<<endl;
    TCanvas *c1 = new TCanvas("c1","c1");
    h1->Draw("e1");
    h1->GetXaxis()->SetTitle("t");
    h1->GetYaxis()->SetTitle("events");
    TCanvas *c2 = new TCanvas("c2","c2");
    h2->Draw("e1");
    TH1F *h3 = new TH1F("h3","h3",50,total * 0.85,total * 1.15);
    for(int i = 0;i < groups;i++)
    {
        h3->Fill(rnd->Gaus(total - 1,sqrt(2 * (total - 1))));
    }
    h3->Draw("samee1");
    h3->SetLineColor(kRed);
    h2->GetXaxis()->SetTitle("(n_{tot}-1)t    (Gaussian)");
    h2->GetYaxis()->SetTitle("events");
    
    TLegend *legend1 = new TLegend(0.7,0.65,0.88,0.85);
    legend1->SetTextFont(72);
    legend1->SetTextSize(0.04);
    legend1->AddEntry(h2,"(n_{tot}-1)t","lpe");
    legend1->AddEntry(h3,"Gaussian","lpe");
    legend1->Draw();
    gStyle->SetOptStat(0);
    c1->SaveAs("h4_5_1.pdf");
    c2->SaveAs("h4_5_2.pdf");
}
