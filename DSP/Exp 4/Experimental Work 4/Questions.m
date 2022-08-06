% Egemen Can Ayduðan - 21728036

clc;

X = fftshift(abs(fft(x)));
Y = fftshift(abs(fft(y)));
faxis = linspace(-1,1,length(x));

figure(1); 
subplot(2,1,1); 
plot(faxis,X);
title('Magnitude Response of X'); xlabel('Normalized Frequency'); ylabel('Magnitude');
subplot(2,1,2); 
plot(faxis,Y);
title('Magnitude Response of Y'); xlabel('Normalized Frequency'); ylabel('Magnitude');

%%
[H1_Num, H1_Den] = tf(H1);
[H2_Num, H2_Den] = tf(H2);
[H3_Num, H3_Den] = tf(H3);

[H1, W1] = freqz(H1_Num, H1_Den);
[H2, W2] = freqz(H2_Num, H2_Den);
[H3, W3] = freqz(H3_Num, H3_Den);

figure;
subplot(2,1,1);
plot(faxis, X); 
title('X Amplitude'); xlabel('Normalized Frequency'); ylabel('Magnitude');
plot(W1/pi, 250*abs(H1)); 
plot(W2/pi, 250*abs(H2));
plot(W3/pi, 250*abs(H3)); 
xlim([-1 1]);
hold off;
legend('X','H3','H2','H1')
subplot(2,1,2);
plot(f_axis, y_amp); grid on;
title_m = title('Y Amplitude'); xlabel('Normalized Frequency'); ylabel('Magnitude');
%%
b1 = Num_but;
a1 = Den_but;
N1 = 4;

b2 = Num_che;
a2 = Den_che;
N2 = 3;

figure; freqz(b1,a1);
figure; freqz(b2,a2);
%%
sound = audioread('s4_1.wav');

y1 = filter(b1,a1,sound);
y2 = filter(b2,a2,sound);

Y1 = fftshift(abs(fft(y1)));
xaxis = linspace(-1,1,length(Y1));
figure; subplot(2,1,1);
plot(xaxis, Y1);
title('Filtered Signal with Butterworth Filter');


Y2 = fftshift(abs(fft(y2)));
xaxis2 = linspace(-1,1,length(Y2)); 
subplot(2,1,2);
plot(xaxis2, Y2);
title('Filtered Signal with Chebychev Type I Filter');