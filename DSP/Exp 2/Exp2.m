b = [1 0.9]; %num
a = [1 -1.0359 0.42]; %den

[y_imp1,n] = impz(b,a,30);
figure(1);
stem(n,y_imp1);

%2_2
N = 30;
x = zeros(1,N);
x(1) = 1;
y_imp2 = filter(b,a,x);
figure(2);
stem(n,y_imp2);

%3
[y_step1,n] = stepz(b,a,30);
figure(3);
stem(n,y_step1);

x = ones(1,30);
y_step2 = filter(b,a,x);
figure(4);
stem(n,y_step2);

%4-5
figure(5);
subplot(2,1,1);
freqz(b,a,30); 
subplot(2,1,2);
stem(n,y_imp1);
    
%% Q2
b1 = [1];
a1 = [1 -1.3762 0.49];
b2 = [1];
a2 = [1 0.8688 0.81];

[h,w] = freqz(b1,a1);
[h2,w2] = freqz(b2,a2);

figure(6);
subplot(2,2,1);
plot(w/pi,20*log10(abs(h)));
subplot(2,2,2);
plot(w2/pi,20*log10(abs(h2)));
subplot(2,2,3);
zplane(b1,a1);
subplot(2,2,4);
zplane(b2,a2);

x_in = randn(1,512);
x_mid = filter(b1,a1,x_in);
x_out = filter(b2,a2,x_mid);

X_in = fftshift(abs(fft(x_in))/length(x_in));
freq_axis1 = linspace(-1,1,length(X_in));

X_mid = fftshift(abs(fft(x_mid))/length(x_mid));
freq_axis2 = linspace(-1,1,length(X_mid));

X_out = fftshift(abs(fft(x_out))/length(x_out));
freq_axis3 = linspace(-1,1,length(X_out));

figure(7);
subplot(3,1,1);
plot(freq_axis1,X_in);
subplot(3,1,2);
plot(freq_axis2,X_mid);
subplot(3,1,3);
plot(freq_axis3,X_out);


    

