% Egemen Can Ayduðan - 21728036
% Preliminary Work 6

function y = dftfilt(x,h,N)

X = fft(x,N);
H = fft(h,N);
y = ifft(X.*H,N);

end