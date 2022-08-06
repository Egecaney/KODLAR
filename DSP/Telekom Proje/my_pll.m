function z = my_pll(y, fc)

    L = length(y);
    Fs = 2*fc;
    kf = 20; 
    
    z = fmdemod(y,fc,2*Fs,kf,0);
    
end