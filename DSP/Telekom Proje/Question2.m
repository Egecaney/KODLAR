clear;
close all;
clc;

% Egemen Can Ayduðan
% 21728036
% ELE326 Homework

% Question 2
%==============================================================================================
% Question 2.A

fm = 50;         % Frequency of square wave is 50 Hz
A = 1;           % Amplitude is 1
duration = 1;
fs = 1e4;
t_axis = 0:1/fs:duration;
x = A*square(2*pi*fm*t_axis);


% Plot of the Spectrum 
X = fft(x);
spectrum_x = abs(fftshift(X))/length(x);
precision_x = fs/length(x);
f = linspace(-fs/2+precision_x/2, fs/2-precision_x/2, length(x));
figure('Name','S(f)');
plot(f,spectrum_x);
grid on;    grid minor;
title('Spectrum of the Message Signal S(f)');      xlabel('Frekans(Hz)');     ylabel('Amplitude(V)');

% Plot of the Magnitude of the Spectrum
magnitude_x = fftshift(abs(X));
figure('Name','Magnitude of S(f)');
plot(f,magnitude_x);
grid on;    grid minor;
title('Magnitude of the Spectrum Message Signal |S(f)|');      xlabel('Frekans(Hz)');     ylabel('Amplitude(V)');

% Plot of the Phase of the Spectrum
phase_x = unwrap(angle(X));
figure('Name','Phase of S(f)');
plot(f,phase_x);
grid on;    grid minor;
title('Phase of the S(f)');     

% With Lowpass Filter fc=60Hz
ylo1 = my_LPF(x,1e4,60);

% Plot of the Spectrum (ylo1)
YLO1 = fft(ylo1);
spectrum_ylo1 = abs(fftshift(YLO1))/length(ylo1);
precision_ylo1 = fs/length(ylo1);
f_ylo1 = linspace(-fs/2+precision_ylo1/2, fs/2-precision_ylo1/2, length(ylo1));
figure('Name','S_ylo1(f)');
plot(f_ylo1,spectrum_ylo1);
grid on;    grid minor;
title('Spectrum of the ylo1 Sylo1(f)');      xlabel('Frekans(Hz)');     ylabel('Amplitude(V)');

% Plot of the Magnitude of the Spectrum (ylo1)
magnitude_ylo1 = fftshift(abs(YLO1));
figure('Name','Magnitude of |S_ylo1(f)|');
plot(f_ylo1,magnitude_ylo1);
grid on;    grid minor;
title('Magnitude of the Spectrum ylo1 |Sylo1(f)|');      xlabel('Frekans(Hz)');     ylabel('Amplitude(V)');

% Plot of the Phase of the Spectrum (ylo1)
phase_ylo1 = unwrap(angle(YLO1));
figure('Name','Phase of S_ylo1(f)');
plot(f_ylo1,phase_ylo1);
grid on;    grid minor;
title('Phase of the Sylo1(f)');     

% With Lowpass Filter fc=200Hz
ylo2 = my_LPF(x,1e4,200);

% Plot of the Spectrum (ylo2)
YLO2 = fft(ylo2);
spectrum_ylo2 = abs(fftshift(YLO2))/length(ylo2);
precision_ylo2 = fs/length(ylo2);
f_ylo2 = linspace(-fs/2+precision_ylo2/2, fs/2-precision_ylo2/2, length(ylo2));
figure('Name','S_ylo2(f)');
plot(f_ylo2,spectrum_ylo2);
grid on;    grid minor;
title('Spectrum of the ylo2 Sylo2(f)');      xlabel('Frekans(Hz)');     ylabel('Amplitude(V)');

% Plot of the Magnitude of the Spectrum (ylo2)
magnitude_ylo2 = fftshift(abs(YLO2));
figure('Name','Magnitude of |S_ylo2(f)|');
plot(f_ylo2,magnitude_ylo2);
grid on;    grid minor;
title('Magnitude of the Spectrum ylo2 |Sylo2(f)|');      xlabel('Frekans(Hz)');     ylabel('Amplitude(V)');

% Plot of the Phase of the Spectrum (ylo2)
phase_ylo2 = unwrap(angle(YLO2));
figure('Name','Phase of S_ylo2(f)');
plot(f_ylo2,phase_ylo2);
grid on;    grid minor;
title('Phase of the Sylo2(f)');  

figure('Name','x(t) - ylo1(t) - ylo2(t)');
plot(t_axis,x,t_axis,ylo1,t_axis,ylo2);
xlim([0.4 0.45]);
ylim([-1.5 1.5]);
grid on;    grid minor;
title('x(t)-ylo1(t)-ylo2(t)'); 

%==============================================================================================
% Question 2.B

% With Highpass Filter fc=100Hz
yhi1 = my_HPF(x,1e4,100);

% Plot of the Spectrum (yhi1)
YHI1 = fft(yhi1);
spectrum_yhi1 = abs(fftshift(YHI1))/length(yhi1);
precision_yhi1 = fs/length(yhi1);
f_yhi1 = linspace(-fs/2+precision_yhi1/2, fs/2-precision_yhi1/2, length(yhi1));
figure('Name','S_yhi(f)');
plot(f_yhi1,spectrum_yhi1);
grid on;    grid minor;
title('The Spectrum yhi |Syhi(f)|');      xlabel('Frekans(Hz)');     ylabel('Amplitude(V)');

% Plot of the Magnitude of the Spectrum (yhi)
magnitude_yhi1 = fftshift(abs(YHI1));
figure('Name','Magnitude of |S_yhi(f)|');
plot(f_yhi1,magnitude_yhi1);
grid on;    grid minor;
title('Magnitude of the Spectrum yhi |Syhi(f)|');      xlabel('Frekans(Hz)');     ylabel('Amplitude(V)');

% Plot of the Phase of the Spectrum (yhi)
phase_yhi1 = unwrap(angle(YHI1));
figure('Name','Phase of S_yhi(f)');
plot(f_yhi1,phase_yhi1);
grid on;    grid minor;
title('Phase of the Shi(f)');  

figure('Name','x(t) - yhi(t)');
plot(t_axis,x,t_axis,yhi1);
xlim([0.4 0.45]);
ylim([-1.5 1.5]);
grid on;    grid minor;
title('x(t)-yhi(t)'); 

%==============================================================================================
% Question 2.C

% With Bandpass Filter fchi = 200Hz && fclo = 100Hz
ybp = my_BPF(x,1e4,100,200);

% Plot of the Spectrum (ybp)
YBP = fft(ybp);
spectrum_ybp = abs(fftshift(YBP))/length(ybp);
precision_ybp = fs/length(ybp);
f_ybp = linspace(-fs/2+precision_ybp/2, fs/2-precision_ybp/2, length(ybp));
figure('Name','S_ybp(f)');
plot(f_ybp,spectrum_ybp);
grid on;    grid minor;
title('The Spectrum ybp |Sybp(f)|');      xlabel('Frekans(Hz)');     ylabel('Amplitude(V)');

% Plot of the Magnitude of the Spectrum (ybp)
magnitude_ybp = fftshift(abs(YBP));
figure('Name','Magnitude of |S_ybp(f)|');
plot(f_ybp,magnitude_ybp);
grid on;    grid minor;
title('Magnitude of the Spectrum yhi |Sybp(f)|');      xlabel('Frekans(Hz)');     ylabel('Amplitude(V)');


% Plot of the Phase of the Spectrum (ybp)
phase_ybp = unwrap(angle(YBP));
figure('Name','Phase of S_ybp(f)');
plot(f_ybp,phase_ybp);
grid on;    grid minor;
title('Phase of the Sbp(f)'); 

figure('Name','x(t) - ybp(t)');
plot(t_axis,x,t_axis,ybp);
xlim([0.4 0.45]);
ylim([-1.5 1.5]);
grid on;    grid minor;
title('x(t)-ybp(t)');

%==============================================================================================


