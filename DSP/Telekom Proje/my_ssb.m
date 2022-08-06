function y = my_ssb(m,fc)

fs = 2*fc;
L = length(m);
t = 0:1/fs:(L-1)/fs;
%Ac = 1;
y1 = 0.5*m.*cos(2*pi*fc*t);
y2 = 0.5*(real(hilbert(m))).*sin(2*pi*fc*t);
y = y1-y2;

end