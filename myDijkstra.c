int mydijkstra() {
    int i, j, l;
    int val, app, diff;
    int a[100], b[100];
    for (i = 0; i < 100; i++) b[i] = 0;
    int dicta[100], dictb[100], dictc[100];
    int ii = 0;
    scanf("%d,", &l);
    for (j = 0; j < d-1; j++) {
        scanf("%d,", &a[j]);
    }
    //printaArray(a, d);
    //printaArray(b, d);

    for (i = 1; i < d; i++) {
        val = a[i-1];
        scanf("%d,", &l);
        for (j = 0; j < d-1; j++) {
            if (i == j+1)  scanf("%d,", &l);
            else {
                scanf("%d,", &app);
                /*if ((a[j] > val + app || a[j] == 0) && (val != 0 && app != 0)) {
                    diff = a[j] - val - app;
                    a[j] -= diff;
                    //check: per ogni el. di a[] con valore in b = j+1  =>  a[l] -= diff;
                    for (l = 0; l < d-1; l++) { //ottimizzo partendo da j e non da 0?
                        if (b[l] == j+1) {
                            a[l] -= diff;
                            b[l] = j+2;
                        }
                    }
                    b[j] = i;
                }*/
                if (app != 0) {
                    if (val != 0 && (a[j] > val + app || a[j] == 0)) {
                        diff = a[j] - val - app;
                        a[j] -= diff;
                        //check: per ogni el. di a[] con valore in b = j+1  =>  a[l] -= diff;
                        for (l = 0; l < d-1; l++) {
                            if (b[l] == j+1) {
                                a[l] -= diff;
                                b[l] = i; //e non j+2
                            }
                        }
                        b[j] = i;
                        //printaArray(a, d);
                        //printaArray(b, d);
                        for (l = 0; l < ii; l++) {
                            if (dictb[l] == j+1) {
                                int ciao = dictc[l] + a[dictb[l]-1];
                                printf("dictc[l] + a[dictb[l]-1] = %d\n", ciao);
                                if (a[dicta[l]-1] > ciao || a[dicta[l]-1] == 0) {
                                    a[dicta[l]-1] = ciao;
                                    b[dicta[l]-1] = dictb[l];
                                    dicta[l] = 0; dictb[l] = 0; dictc[l] = 0;
                                }
                            }
                        }
                    }
                    else if (val == 0) {
                        dicta[ii] = j+1;
                        dictb[ii] = i;
                        dictc[ii] = app;
                        ii++;
                        printf("Aggiunta al dizionario la entry %d|%d|%d\n", j+1, i, app);
                    }
                }

            }
        }
        //printaArray(a, d);
        //printaArray(b, d);
    }
}