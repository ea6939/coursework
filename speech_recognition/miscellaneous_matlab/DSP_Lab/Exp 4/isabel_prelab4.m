     v1 = 0.2
     v2 = 0.1;
     v3 = 0.05;
     v4 = 0.65;
     prob = [v1 v2 v3 v4];
     H = 0;
     
     for i=1:4
        H = H -prob(i)*log2(prob(i))
     end
     