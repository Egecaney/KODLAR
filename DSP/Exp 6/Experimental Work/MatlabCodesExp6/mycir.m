function y = mycir(x,h,N)

L_x = length(x);
L_h = length(h);

%zero padding
x = [x,zeros(1,N - L_x)];
h_zp = [h, zeros(1,N-L_h)];

h_r = [h(1), fliplr(h_zp(2:end))];
toe = toeplitz(h_r,h_zp);
y = x*toe;

end