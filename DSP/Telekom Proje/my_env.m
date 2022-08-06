function y = my_env(s,fc)

Fs = 2*fc;
h1 = abs(hilbert(s));
a1 = h1.^2 + s.^2;
a2 = sqrt(a1);
y = my_LPF(a2,Fs,fc);

end