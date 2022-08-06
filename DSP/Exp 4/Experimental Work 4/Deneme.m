clc;

sgnls = load('signals4.mat');
x = sgnls.x;
y = sgnls.y;
X = fftshift(abs(fft(x)));
Y = fftshift(abs(fft(y)));
FXaxis = linspace(-1,1,length(x));

% Question 1 Yorum
% When I compare the filters, I can easily see that the second filter is the correct one. 
% Both the first peaks to be equal and the second peaks from the cutting point.

% Question 2
[b1, a1] = tf(H2);
[filterx] = freqz(b1,a1);
% b1 = 0.0089 0.0357 0.0535 0.0089
% a1 = 1.0000 -2.0480 1.8413 -0.7822 0.1316
% N1 = 4

% Question 3
[b2, a2] = tf(Hnew);
[filterx2] = freqz(b2,a2);
% b2 = 0.0110 0.0329 0.0329 0.0110
% a2 = 1.000 -2.1776 1.8633 -0.5980
% N2 = 3

% Question 4
% Chebyshev Filter Type 1 have ripples on the top values and falling very high slope.
% Butterworth Filter more slow than Chebyshev and don't have ripples.

% Question 5
[sound4, fs] = audioread('s4_1.wav');
Sound4 = fftshift(abs(fft(sound4)));
FreqAxisSound4 = linspace(-1,1-1/length(Sound4),length(Sound4));

y1 = filter(b1,a1,sound4);
Y1 = fftshift(abs(fft(y1)));
FY1 = linspace(-1,1,length(y1));

y2 = filter(b2,a2,sound4);
Y2 = fftshift(abs(fft(y2)));
FY2 = linspace(-1,1,length(y2));

figure(1);
subplot(2,1,1);
plot(FY1,Y1);
title('Butterworth Filter'); ylabel('Magnitude'); xlabel('Normalized Frequency');
subplot(2,1,2);
plot(FY2,Y2);
title('Chebyshev Filter Type 1'); ylabel('Magnitude'); xlabel('Normalized Frequency');

% Butterworth Filter is chosen for having good amplitude.
% But Chebyshev filter is chosen for having good frequency selecting.
