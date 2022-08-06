function y = my_ampmod(m,fc)

c = length(m);
fs = 2*fc;
Ac = 1;
ka = 1;
t = 0:1/fs:(((c-1)/fs));
y = (Ac*(1+ka*m)).*cos(2*pi*fc*t); 

end