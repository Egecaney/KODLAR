function [y] = my_dsbsc(m,fc)

c = length(m);
fs = 2*fc;
t = 0:1/fs:(((c-1)/fs));
%Ac = 1;
y = m.*cos(2*pi*fc*t); 

end