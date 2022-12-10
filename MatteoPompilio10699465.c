#include <stdio.h> //MatteoPompilio10699465
#include <stdlib.h>
#include <stdint.h>

int d, k, heapSize;

void leggiGrafo(uint32_t m[d][d], char s_input2[]) {
    register int a, b, l;
	uint32_t v;
    getchar();
    for (a = 0; a < d; a++) {
        l = 0;
        if (fgets(s_input2, 11*d, stdin) != NULL) {
            for (b = 0; b < d; b++) {
                v = 0;
                if (a == b || b == 0) {
                    m[a][b] = 0;
                    while (s_input2[l] != ',' && s_input2[l] != '\n') l++;
                    l++;
                }
                else {
                    while (s_input2[l] != ',' && s_input2[l] != '\n') {
                        v = v + v + v + v + v + v + v + v + v + v;
                        v = v + (s_input2[l] - 48);
                        l++;
                    }
                    l++;
                    m[a][b] = v;
                }
            }
        }
    }
}

void minHeapify(uint32_t heapD[], uint32_t heapI[], int R2[], int a) {
    uint32_t temp;
    register int min;
    int b = a + a + 1;
    int c = a + a + 2;
    if (b < heapSize && (heapD[b] < heapD[a])) min = b;
    else min = a;
    if (c < heapSize && heapD[c] < heapD[min]) min = c;
    if (min != a) {
        R2[heapI[a]-1] = min;
        R2[heapI[min]-1] = a;
        temp = heapD[a]; heapD[a] = heapD[min]; heapD[min] = temp;
        temp = heapI[a]; heapI[a] = heapI[min]; heapI[min] = temp;
        minHeapify(heapD, heapI, R2, min);
    }
}

void maxHeapify(uint32_t F1[], uint32_t F2[], int a) {
    uint32_t temp;
    register int max;
    int b = a + a + 1;
    int c = a + a + 2;
    if (b < k && (F1[b] > F1[a])) max = b;
    else max = a;
    if (c < k && F1[c] > F1[max]) max = c;
    if (max != a) {
        temp = F1[a]; F1[a] = F1[max]; F1[max] = temp;
        temp = F2[a]; F2[a] = F2[max]; F2[max] = temp;
        maxHeapify(F1, F2, max);
    }
}

void decrementaChiave(uint32_t heapD[], uint32_t heapI[], int R2[], uint32_t dist, int i) {
    uint32_t temp;
    register int p;
    heapD[i] = dist;
    if (i != 0) p = (i-1)/2;
    else R2[heapI[i]-1] = 0;

    while (i != 0 && heapD[p] > heapD[i]) {
        R2[heapI[i]-1] = p;
        R2[heapI[p]-1] = i;
        temp = heapD[i]; heapD[i] = heapD[p]; heapD[p] = temp;
        temp = heapI[i]; heapI[i] = heapI[p]; heapI[p] = temp;
        i = (i-1)/2;
        p = (i-1)/2;
    }
}

void accodaMin(uint32_t heapD[], uint32_t heapI[], int R2[], uint32_t dist, int i) {
    register int a = heapSize, p = 0;
    uint32_t temp;
    heapSize++;
    heapD[a] = dist;
    heapI[a] = i;
    R2[heapI[a]-1] = a;
    if (a != 0) p = (a-1)/2;

    while (a != 0 && heapD[p] > heapD[a]) {
        R2[heapI[a]-1] = p;
        R2[heapI[p]-1] = a;
        temp = heapD[a]; heapD[a] = heapD[p]; heapD[p] = temp;
        temp = heapI[a]; heapI[a] = heapI[p]; heapI[p] = temp;
        a = (a-1)/2;
        p = (a-1)/2;
    }
}

void cancellaMin(uint32_t heapD[], uint32_t heapI[], int R2[], uint32_t *a, int *b) {
    (*a) = heapD[0];
    (*b) = heapI[0];
    heapSize--;
    R2[heapI[0]-1] = -1;
    R2[heapI[heapSize]-1] = 0;
    heapD[0] = heapD[heapSize];
    heapI[0] = heapI[heapSize];
    minHeapify(heapD, heapI, R2, 0);
}

uint32_t myDijkstra(uint32_t m[d][d], uint32_t heapD[], uint32_t heapI[], uint32_t R1[], int R2[]) {
    heapSize = 0;
    uint32_t a, value = 0;
	register int i;
    int b;

    for (i = 1; i < d; i++) {
        R1[i-1] = 0;
        R2[i-1] = -1;
        if (m[0][i] != 0) accodaMin(heapD, heapI, R2, m[0][i], i);
    }
    while (heapSize != 0) {
        cancellaMin(heapD, heapI, R2, &a, &b);
        if (R1[b-1] == 0) {
            R1[b-1] = a;
            for (i = 1; i < d; i++) {
                if (m[b][i] != 0) {
                    if (R1[i-1] == 0) {
                        if (R2[i-1] == -1)
                            accodaMin(heapD, heapI, R2, m[b][i]+a, i);
                        else if (heapD[R2[i-1]] > m[b][i]+a) 
                            decrementaChiave(heapD, heapI, R2, m[b][i]+a, R2[i-1]);
                    }
                }
            }
        }
    }
    for (i = 0; i < d-1; i++) value += R1[i];
    return value;
}

int main() {
    if (scanf("%d %d", &d, &k) && d != 0) {
        char s_input1[14];
        uint32_t val;
        register int a = 0;
        uint32_t (*m)[d]; 
        m = (uint32_t (*)[d])malloc(sizeof(*m) * d);
        char *s_input2 = (char *)malloc((11*d) * sizeof(char));
        uint32_t *heapD = (uint32_t *)malloc((d-1) * sizeof(uint32_t)); //distanze nel min_heap_dijsktra
        uint32_t *heapI = (uint32_t *)malloc((d-1) * sizeof(uint32_t)); //indici relativi
        uint32_t *R1 = (uint32_t *)malloc((d-1) * sizeof(uint32_t)); //distanze finali del grafo j-esimo
        int *R2 = (int *)malloc((d-1) * sizeof(int)); //R2[i] = 1 se l'i-esimo nodo del j-esimo grafo è stato inserito in R1, 0 altrimenti
        uint32_t *F1 = (uint32_t *)calloc(k, sizeof(uint32_t)); //distanze nel max_heap_topk
        uint32_t *F2 = (uint32_t *)calloc(k, sizeof(uint32_t)); //indici relativi <=> output

        while (fgets(s_input1, 14, stdin) != NULL) {
            if (s_input1[0] == 'A') {
                leggiGrafo(m, s_input2);
                val = myDijkstra(m, heapD, heapI, R1, R2);
                if (a < k) {
                    F1[a] = val;
                    F2[a] = a;
                }
                else if (a == k) {
                    for (register int c = (k/2); c--;) maxHeapify(F1, F2, c);
                    if (val < F1[0]) {
                        F1[0] = val;
                        F2[0] = a;
                        maxHeapify(F1, F2, 0);
                    }
                }
                else if (a > k && val < F1[0]) {
                    F1[0] = val;
                    F2[0] = a;
                    maxHeapify(F1, F2, 0);
                }
                a++;
            }
            else if (s_input1[0] == 'T') {
                if (a != 0) {
                    register int f = a, j;
                    if (a > k) f = k;
                    for (j = 0; j < f-1; j++) printf("%d ", F2[j]);
                    printf("%d\n", F2[j]);
                }
                else printf("\n");
            }
        }
        free(m);
        free(s_input2);
        free(heapD);
        free(heapI);
        free(R1);
        free(R2);
        free(F1);
        free(F2);
    }
    return 0;
}
