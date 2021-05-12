import ROOT as r

#open rootfile

f=r.TFile.Open("YourApplication.root")

#get directory as tree

t=f.Get("histograms")

#get the histograms

edep=t.Get("Edep")
trackL=t.Get("trackL")

#create canvas

c=r.TCanvas("c","",20,20,1000,1000)
c.Divide(1,2)

c.cd(1)
edep.Draw("hist")

c.cd(2)
trackL.Draw("hist")

c.Print("plot.png","png")