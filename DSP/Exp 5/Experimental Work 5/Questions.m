% Experimental Work 5
% Egemen Can Ayduðan - 21728036

%% Question 2

w21 = mybart(24);
W21 = 10*log10(fftshift(abs(fft(w21,1000))/length(w21)));
freq_W21 = linspace(-1,1-1/length(W21),length(W21));

w22 = mybart(99);
W22 = 10*log10(fftshift(abs(fft(w22,1000))/length(w22)));
freq_W22 = linspace(-1,1-1/length(W22),length(W22));

w23 = mybart(399);
W23 = 10*log10(fftshift(abs(fft(w23,1000))/length(w23)));
freq_W23 = linspace(-1,1-1/length(W23),length(W23));

figure(1);
subplot(3,1,1);
plot(freq_W21, W21);
title('Magnitude Spectrum of Bartlett Window W_2_1 (M=24)');
subplot(3,1,2);
plot(freq_W22, W22);
title('Magnitude Spectrum of Bartlett Window W_2_2 (M=99)');
subplot(3,1,3);
plot(freq_W23, W23);
title('Magnitude Spectrum of Bartlett Window W_2_3 (M=399)');

%% Question 3
load('signal1_5.mat');
figure(2);
plot(sin_x); title('Original Signal Sin_x');

rec24 = myrec(24);
rec99 = myrec(99);
FreqAxis = linspace(-1,1,length(sin_x));

%3.1
x_r1 = sin_x.*[rec24(1:25) zeros(1,length(sin_x)-25)];
X_R1 = 10*log10(fftshift(abs(fft(x_r1,length(sin_x)))/length(x_r1)));
freq_X_R1 = linspace(-1,1-1/length(X_R1),length(X_R1));

x_r2 = sin_x.*[rec99(1:100) zeros(1,length(sin_x)-100)];
X_R2 = 10*log10(fftshift(abs(fft(x_r2,length(sin_x)))/length(x_r2)));
freq_X_R2 = linspace(-1,1-1/length(X_R2),length(X_R2));

figure(3);
subplot(2,1,1);
plot(freq_X_R1,X_R1);
title('Windowed Signal with Rectangular Window (L=25)');
subplot(2,1,2);
plot(freq_X_R2,X_R2);
title('Windowed Signal with Rectangular Window (L=100)');

%3.2
x_bt1 = sin_x.*[w21(1:25) zeros(1,length(sin_x)-25)];
X_BT1 = 10*log10(fftshift(abs(fft(x_bt1,length(sin_x)))/length(x_bt1)));
freq_X_BT1 = linspace(-1,1-1/length(X_BT1),length(X_BT1));

x_bt2 = sin_x.*[w22(1:100) zeros(1,length(sin_x)-100)];
X_BT2 = 10*log10(fftshift(abs(fft(x_bt2,length(sin_x)))/length(x_bt2)));
freq_X_BT2 = linspace(-1,1-1/length(X_BT2),length(X_BT2));

figure(4);
subplot(2,1,1);
plot(freq_X_BT1,X_BT1);
title('Windowed Signal with Bartlett Window (L=25)');
subplot(2,1,2);
plot(freq_X_BT2,X_BT2);
title('Windowed Signal with Bartlett Window (L=100)');

%% Question 4
load('signal2_5.mat');
figure(5);
subplot(2,1,1);
plot(x1); title('Original Signal x_1');
subplot(2,1,2);
plot(y1); title('Original Signal y_1');

X1 = fftshift(abs(fft(x1)));
Y1 = fftshift(abs(fft(y1)));
FreqAxisXY = linspace(-1,1,512);

figure(6);
subplot(2,1,1);
plot(FreqAxisXY,X1); title('FFT of X_1');
subplot(2,1,2);
plot(FreqAxisXY,Y1); title('FFT of Y_1');

wn = [0.42 0.46];
h1 = fir1(30,wn);
y_out = filter(h1,1,x1);
Y_out=fftshift(abs(fft(y_out)));

figure(7);
subplot(2,2,4);
plot(FreqAxisXY,Y_out); title('Filtered FFT of X_1 (Y_o_u_t)');
subplot(2,2,3);
plot(FreqAxisXY,Y1); title('FFT of Y_1');
subplot(2,2,1);
plot(y1); title('Original Signal y_1');
subplot(2,2,2);
plot(y_out); title('Filtered X_1 Signal (y_o_u_t)');

%% Question 6
[y,fsample] = audioread('S1_5.wav');
Y = (fftshift(abs(fft(y))));
freq_Y = linspace(-1,1,length(Y));

h2 = fir1(50,0.2,'low',mybart(50));
y2 = filter(h2,1,y);
Y2 = (fftshift(abs(fft(y2))));
freq_Y2 = linspace(-1,1,length(Y2));

y3 = myConv(y,h2);
Y3 = (fftshift(abs(fft(y3))));
freq_Y3= linspace(-1,1,length(Y3));

figure(8);
subplot(3,1,1);
plot(freq_Y,Y); title('Original');
subplot(3,1,2);
plot(freq_Y2,Y2); title('Filtered Sound File');
subplot(3,1,3);
plot(freq_Y3,Y3); title('With Convolution Function');



