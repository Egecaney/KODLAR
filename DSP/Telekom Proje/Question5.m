%% Egemen Can Ayduðan
% 21728036
% ELE326 Final Project
% QUESTION 5
[s,Fs] = audioread('sound_file.wav');       
original = audioplayer(s,Fs);

L = length(s);
t = 0:1/Fs:(L-1)/Fs;
S = imag(fftshift(fft(s)));                 
S_mag = abs(S);                             
f_axis = -Fs/2:Fs/L:(Fs/2-Fs/L);

figure(1);
x1 = subplot(3,1,1);
plot(x1,t,s);          
grid on;    
grid minor;
title('Original Message Signal');      xlabel('Time(s)');     ylabel('Amplitude(V)');

x2 = subplot(3,1,2);
plot(x2,f_axis,S);       
grid on;    
grid minor;
title('Spectrum of the Message Signal S(jw)');      xlabel('Frequency(Hz)');    ylabel('Amplitude');

x3 = subplot(3,1,3);
plot(x3,f_axis,S_mag);   grid on;    grid minor;
title('|S(jw)|');       xlabel('Frequency (Hz)');   ylabel('Magnitude');

fcut = 1500;                
sft = my_LPF(s,Fs,fcut);
S_f = imag(fftshift(fft(sft)));      
S_f_mag = abs(S_f);                 
lpf = audioplayer(sft,Fs);

figure(2);
x1 = subplot(3,1,1);
plot(x1,t,sft);          grid on;      grid minor;
title('Lowpass Filtered Message Signal (fcut = 1500 Hz)');      xlabel('Time (s)');     ylabel('Amplitude (V)');

x2 = subplot(3,1,2);
plot(x2,f_axis,S_f);       grid on;    grid minor;
title('Spectrum of the Message Signal Sf(jw)');      xlabel('Frequency(Hz)');    ylabel('Amplitude');

x3 = subplot(3,1,3);
plot(x3,f_axis,S_f_mag);   grid on;    grid minor;
title('|Sf(jw)|');       xlabel('Frequency (Hz)');   ylabel('Magnitude');

%% Question 5.A 
% Modulation Type: AM Modulation  ,  Demodulation Type: Coherent Detector
% AM Modulation: 
fc = Fs/480;                   
sm = transpose(my_ampmod(transpose(sft),fc)); 
figure(3);
x4 = subplot(2,1,1);
plot(x4,t,sm);     grid on;    grid minor;
title('Amplitude Modulated Signal Sm(t)');      xlabel('Time(s)');     ylabel('Amplitude(V)');

sd = transpose(my_coh(transpose(sm),fc));
sd = sd - mean(sd);                   
demod_d = audioplayer(sd,Fs);             
x5 = subplot(2,1,2);
plot(x5,t,sd);      grid on;    grid minor;
title('Coh Demodulated Signal Sd(t)');     xlabel('Time(s)');     ylabel('Amplitude(V)');

% Coherent Detection:
fcut = 1500;                
sr = my_LPF(sd,Fs,fcut);
S_r = imag(fftshift(fft(sr)));     
recon_d = audioplayer(sr,Fs);     
figure(4);
x6 = subplot(2,1,1);
plot(x6,t,sr);          grid on;    grid minor;
title(' Filtered Message Signal (fcut = 1500 Hz)');      xlabel('Time(s)');     ylabel('Amplitude(V)');
x7 = subplot(2,1,2);
plot(x7,f_axis,S_r);       grid on;    grid minor;
title('Spectrum of the message signal Sr(jw)');      xlabel('Frequency(Hz)');    ylabel('Amplitude');

%% Question 5.B 
% Modulation Type: DSB-SC Modulation  ,  Demodulation Type: Coherent Detector
% DSB-SC Modulation:
fc = Fs/480;                  
sm = transpose(my_dsbsc(transpose(sft),fc));     
figure(5);
x4 = subplot(2,1,1);
plot(x4,t,sm);     grid on;    grid minor;
title('DSB-SC Modulated Signal Sm(t)');      xlabel('Time(s)');     ylabel('Amplitude(V)');

sd = transpose(my_coh(transpose(sm),fc));
sd = sd - mean(sd);                     
demod_e = audioplayer(sd,Fs);             
x5 = subplot(2,1,2);
plot(x5,t,sd);      grid on;    grid minor;
title('Coherent Demodulated Signal Sd(t)');     xlabel('Time(s)');     ylabel('Amplitude(V)');

% Coherent Demodulation
fcut = 1500;               
sr = my_LPF(sd,Fs,fcut);
S_r = imag(fftshift(fft(sr)));      
recon_e = audioplayer(sr,Fs);     
figure(6);
x6 = subplot(2,1,1);
plot(x6,t,sr);          grid on;    grid minor;
title(' Filtered Message Signal (fcut = 1500 Hz)');      xlabel('Time(s)');     ylabel('Amplitude(V)');

x7 = subplot(2,1,2);
plot(x7,f_axis,S_r);       grid on;    grid minor;
title('Spectrum of the Message Signal Sr(jw)');      xlabel('Frequency(Hz)');    ylabel('Amplitude(V)');

%% Question 5.C
% Modulation Type: SSB Modulation  ,  Demodulation Type: Coherent Detector
% SSB Modulation:
fc = Fs/480;                  
sm = transpose(my_ssb(transpose(sft),fc));     
figure(7);
x4 = subplot(2,1,1);
plot(x4,t,sm);     grid on;    grid minor;
title('SSB Modulated Signal Sm(t)');      xlabel('Time(s)');     ylabel('Amplitude(V)');

sd = transpose(my_coh(transpose(sm),fc));
sd = sd - mean(sd);                     
demod_f = audioplayer(sd,Fs);            
x5 = subplot(2,1,2);
plot(x5,t,sd);      grid on;    grid minor;
title('Coherent Demodulated Signal Sd(t)');     xlabel('Time(s)');     ylabel('Amplitude(V)');

% Coherent Demodulation
fcut = 1500;                % cutoff frequency
sr = my_LPF(sd,Fs,fcut);
S_r = imag(fftshift(fft(sr)));      
recon_f = audioplayer(sr,Fs);     
figure(8);
x6 = subplot(2,1,1);
plot(x6,t,sr);          grid on;    grid minor;
title(' Filtered Message Signal (fcut = 1500 Hz)');      xlabel('Time(s)');     ylabel('Amplitude (V)');
x7 = subplot(2,1,2);
plot(x7,f_axis,S_r);       grid on;    grid minor;
title('Spectrum of the Message Signal Sr(jw)');      xlabel('Frequency(Hz)');    ylabel('Amplitude');

%% Question 5.D
% Modulation Type: AM Modulation  ,  Demodulation Type: Envelope Detector
% AM Modulation:
fc = Fs/480;                  
sm = transpose(my_ampmod(transpose(sft),fc));     
figure(9);
x4 = subplot(2,1,1);
plot(x4,t,sm);     grid on;    grid minor;
title('Amplitude Modulated Signal Sm(t)');      xlabel('Time(s)');     ylabel('Amplitude(V)');

sd = transpose(my_env(transpose(sm),fc));
sd = sd - mean(sd);                     
demod_g = audioplayer(sd,Fs);            
x5 = subplot(2,1,2);
plot(x5,t,sd);      grid on;    grid minor;
title('Envelope Demodulated Signal Sd(t)');     xlabel('Time(s)');     ylabel('Amplitude(V)');

% Envelope Demodulation:
fcut = 1500;              
sr = my_LPF(sd,Fs,fcut);
S_r = imag(fftshift(fft(sr)));      
recon_g = audioplayer(sr,Fs);    
figure(10);
x6 = subplot(2,1,1);
plot(x6,t,sr);          grid on;    grid minor;
title(' Filtered message signal (fcut = 1500 Hz)');      xlabel('Time(s)');     ylabel('Amplitude(V)');

x7 = subplot(2,1,2);
plot(x7,f_axis,S_r);       grid on;    grid minor;
title('Spectrum of the message signal Sr(jw)');      xlabel('Frequency(Hz)');    ylabel('Amplitude(V)');

%% Question 5.E 
% Modulation Type: DSB-SC Modulation  ,  Demodulation Type: Envelope Detector 
% DSB-SC Modulation
fc = Fs/480;                   
sm = transpose(my_dsbsc(transpose(sft),fc));   
figure(11);
x4 = subplot(2,1,1);
plot(x4,t,sm);     grid on;    grid minor;
title('DSB-SC Modulated signal Sm(t)');      xlabel('Time(s)');     ylabel('Amplitude(V)');

sd = transpose(my_env(transpose(sm),fc));
sd = sd - mean(sd);                    
demod_h = audioplayer(sd,Fs);             
x5 = subplot(2,1,2);
plot(x5,t,sd);      grid on;    grid minor;
title('Envelope Demodulated Signal Sd(t)');     xlabel('Time(s)');     ylabel('Amplitude(V)');

% Envelope Demodulation:
fcut = 1500;                
sr = my_LPF(sd,Fs,fcut);
S_r = imag(fftshift(fft(sr)));      
recon_h = audioplayer(sr,Fs);     
figure(12);
x6 = subplot(2,1,1);
plot(x6,t,sr);          grid on;    grid minor;
title(' Filtered Message Signal (fcut = 1500 Hz)');      xlabel('Time(s)');     ylabel('Amplitude(V)');

x7 = subplot(2,1,2);
plot(x7,f_axis,S_r);       grid on;    grid minor;
title('Spectrum of the Message Signal Sr(jw)');      xlabel('Frequency(Hz)');    ylabel('Amplitude(V)');

%% Question 5.F 
% Modulation Type: SSB Modulation  ,  Demodulation Type: Envelope Detector 
% SSB Modulation:
fc = Fs/480;                   
sm = transpose(my_ssb(transpose(sft),fc));    
figure(13);
x4 = subplot(2,1,1);
plot(x4,t,sm);     grid on;    grid minor;
title('SSB Modulated Signal Sm(t)');      xlabel('Time(s)');     ylabel('Amplitude(V)');

sd = transpose(my_env(transpose(sm),fc));
sd = sd - mean(sd);                     
demod_i = audioplayer(sd,Fs);             
x5 = subplot(2,1,2);
plot(x5,t,sd);      grid on;    grid minor;
title('Envelope Demodulated Signal Sd(t)');     xlabel('Time(s)');     ylabel('Amplitude(V)');

% Envelope Demodulation:
fcut = 1500;                
sr = my_LPF(sd,Fs,fcut);
S_r = imag(fftshift(fft(sr)));    
recon_i = audioplayer(sr,Fs);     
figure(14);
x6 = subplot(2,1,1);
plot(x6,t,sr);          grid on;    grid minor;
title(' Filtered Message Signal (fcut = 1500 Hz)');      xlabel('Time(s)');     ylabel('Amplitude(V)');

x7 = subplot(2,1,2);
plot(x7,f_axis,S_r);       grid on;    grid minor;
title('Spectrum of the Message Signal Sr(jw)');      xlabel('Frequency(Hz)');    ylabel('Amplitude(V)');
%% Question 5.G
% Modulation Type: FM Modulation  ,  Demodulation Type: PLL 
% FM Modulation:
fc = Fs/480;                  
sm = transpose(my_fm(transpose(sft),fc));    
figure(15);
x4 = subplot(2,1,1);
plot(x4,t,sm);     grid on;    grid minor;
title('FM Modulated Signal Sm(t)');      xlabel('Time (s)');     ylabel('Amplitude (V)');

sd = transpose(my_pll(transpose(sm),fc));
sd = sd - mean(sd);                     
demod_j = audioplayer(sd,Fs);             
x5 = subplot(2,1,2);
plot(x5,t,sd);      grid on;    grid minor;
title('PLL Demodulated Signal Sd(t)');     xlabel('Time (s)');     ylabel('Amplitude (V)');

% PLL Demodulation
fcut = 1500;                
sr = my_LPF(sd,Fs,fcut);
S_r = imag(fftshift(fft(sr)));     
recon_j = audioplayer(sr,Fs);     
figure(16);
x6 = subplot(2,1,1);
plot(x6,t,sr);          grid on;    grid minor;
title(' Filtered Message Signal (fcut = 1500 Hz)');      xlabel('Time(s)');     ylabel('Amplitude(V)');

x7 = subplot(2,1,2);
plot(x7,f_axis,S_r);       grid on;    grid minor;
title('Spectrum of the Message Signal Sr(jw)');      xlabel('Frequency (Hz)');    ylabel('Amplitude(V)');