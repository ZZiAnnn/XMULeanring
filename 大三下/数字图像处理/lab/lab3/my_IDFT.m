function gp = my_IDFT(G)
    [M, N] = size(G);
    u = 0:M-1;
    v = 0:N-1;
    x = u';
    y = v';

    eM = exp(2j * pi * (x * u) / M);
    eN = exp(2j * pi * (y * v) / N);

    gp = (eM * G * eN) / (M * N);
end