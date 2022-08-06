function y = dft(x,h,N)

X = fft(x,N);
H = fft(h,N);
Y = X.*H;
y = ifft(Y,N);

end