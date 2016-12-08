for i = 1:n,
    k = i
    for j = i+1:n, if a[j] < a[k], k = j
    ? invariant: a[k] smallest of a[i..n]
    swap a[i,k]
    ? invariant: a[1..i] in final position
end
