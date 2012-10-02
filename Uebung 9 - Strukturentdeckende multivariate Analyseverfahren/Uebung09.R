# Erstellen der Matrix A
A=rbind(c(1, 8, 2, 6, 8, 4, 8, 5 ), c(2, 8, 3, 7, 9, 6, 9, 8), c(7, 3, 5, 2, 1,  5, 1, 7))

# Mittelwerte der Variablen
mean(A[1,])
mean(A[2,])
mean(A[3,])

# Varianzen der Variablen
var(A[1,])
var(A[2,])
var(A[3,])

# Kovarianzen der Variablen
cov(A[1,], A[2,])
cov(A[1,], A[3,])
cov(A[2,], A[3,])

# Korrelationskoeffizienten der Variablen
cor(A[1,], A[2,])
cor(A[1,], A[3,])
cor(A[2,], A[3,])

# Zusatzaufgabe
CorA=cor(A)
VarA=var(A)
d=dist(A, method="euclidean")
fit=hclust(d, method="ward")
plot(fit)

