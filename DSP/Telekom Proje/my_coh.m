function [z] = my_coh(y, fc)

    L = length(y);
    Fs = 2*fc;
    t = 0:1/Fs:(L-1)/Fs;
    
    y1 = y.*cos(2*pi*fc*t);
    z = my_LPF(y1,Fs,fc/10);
    
end
