function [y] = overlapadd_cir(x,h,L)
N = length(x);
P = length(h);
M = N / L ;
y = conv(x(1:L),h);
w = [y((L+1):(L+P-1))]; 
w(P:L) = 0;
for counter = 2:M
    index = (counter - 1) * L + 1;
    z = conv(x(index:(index+L-1)),h); 
    y(index:(index+L-1)) = z(1:L) + w(1:L);
    w = [z((L+1):(L+P-1))] ;
    w(P:L) = 0;

end
