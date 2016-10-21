/* This file contains random pieces of code that might be useful one day. */

    /* I wanted to find out how many rows does the design matrix have.  */
//    vector<int> uiop(Design_m->nz);
//    
//    for(int i=0; i < uiop.size(); i++)
//    { 
//        uiop[i] = Design_m->i[i];
//    }
//    
//    sort(uiop.begin(), uiop.end(), [&](int a, int b) -> bool { return a < b; });
//    
//    auto UniqueIterator = unique(uiop.begin(), uiop.end(), [&](int a, int b) -> bool { return a == b; });
//    uiop.erase(UniqueIterator, uiop.end());
//    
//    cout << uiop.size() << endl;

//=========================

/* This applies fitmask to mass axis and signal vectors */
//    /* Mass axis, signal, fitmask */
//    vector<tuple<double, double, bool> > MassSigMaskTuple(dataLength);
//    
//    for(int i=0; i < dataLength; i++)
//    { 
//        get<0>(MassSigMaskTuple[i]) = MassAxis[i];
//        get<1>(MassSigMaskTuple[i]) = Signal[i];
//        get<2>(MassSigMaskTuple[i]) = FitMask[i];
//    }
//    
////    cout << MassSigMaskTuple.size() << endl;
//
//    auto itrtr = remove_if(MassSigMaskTuple.begin(), MassSigMaskTuple.end(), [&](tuple<double, double, bool> A) -> bool { return !get<2>(A); });
//    MassSigMaskTuple.erase(itrtr, MassSigMaskTuple.end());
//    
//    /* Update the data length */
//    dataLength = MassSigMaskTuple.size();

//=========================

//    /* Building the compressed design matrix. We do this after masking the signal vector, because now we know how many rows will the resulting matrix have. */    
//    /* Sort the sparse matrix by rows. */
//    /* Row, column, data */
//    cout << Design_m->nz << endl;
//    vector<tuple<int, int, double> > DesignSort (Design_m->nz);
//    
//    for(int i=0; i < DesignSort.size(); i++)
//    { 
//        get<0>(DesignSort[i]) = Design_m->i[i];
//        get<1>(DesignSort[i]) = Design_m->p[i];
//        get<2>(DesignSort[i]) = Design_m->data[i];
//    }
//    
//    /* Sorts by rows */
//    sort(DesignSort.begin(), DesignSort.end(), [&](tuple<int,int,double> A, tuple<int,int,double> B) -> bool { return get<0>(A) < get<0>(B); });
//    
//    /* Now fill the data into the compressed matrix, disregarding row indices. they will be used only to chceck if we are writing to the same row. */
//    cout << dataLength << endl;
//    gsl_spmatrix *DesignComp_m = gsl_spmatrix_alloc(dataLength, moleculeCount);
//       
////    ofstream dessort;
////    dessort.open("dessort");
////    for(int i=0; i<DesignSort.size(); i++)
////    {
////        dessort << get<0>(DesignSort[i]) << " " << get<1>(DesignSort[i]) << " " << get<2>(DesignSort[i]) << endl;
////    }
////    dessort.close();
//    
//    int rowIndex = 0;
//    
//    /* Go through every data element in the sorted design matrix. */
//    for(int i = 0; i < DesignSort.size(); i++)
//    {
//        /* And write it to the correct column of the actual row. */
//        gsl_spmatrix_set(DesignComp_m, rowIndex, get<1>(DesignSort[i]), get<2>(DesignSort[i]));
//
//        /* If the next data element is assigned to the next row, increment the row index. */
//        if(get<0>(DesignSort[i]) != get<0>(DesignSort[i + 1])) rowIndex++;
//    }
//    
//    cout << rowIndex << endl;
    
//    char* gue[1] = {"%f"};
//    FILE *mtrx = fopen("designsortmatrix", "w");
//    gsl_spmatrix_fprintf(mtrx, DesignComp_m, *gue);
//    fclose(mtrx);
    
//    cout << DesignComp_m->nz << endl;

//========================

/* This reads a submatrix from the sparse design matrix and accumulates it into the tsqr workspace. At least is supposed to, program was not giving correct resullts with this. */
        //TODO: here
    /* Strategy:
     *  Read a submatrix of the compressed sparse design matrix.
     *  Turn the sparse submatrix into dense one.
     *  Transform it to the standard form.
     *  Accumulate.
     *  Repeat.
     */
////    gsl_spmatrix *DesignCompSub_m;
//    gsl_matrix *DesignCompSub_mDens;
//    gsl_vector *SignalSub_v;
//    
//    gsl_matrix *DesignCompSubStd_m;
//    gsl_vector *SignalSubStd_v;
//    
//    int blockIndex = 0;
//    int rowsLeft = MassSigMaskTuple.size();
//    int blockSize = 1000;  //size of one block to accumulate, num of rows moleculeCount MassSigMaskTuple.size();
//    
//    int rowIndex2;
//    int elementIndex = 0;
//    
//    FILE *mtrx;
//    
//    cout << moleculeCount << endl;
//    cout << rowsLeft << endl;
//    cout << get<0>(DesignSort[DesignSort.size()-1]) << " " << get<1>(DesignSort[DesignSort.size()-1]) << " " << get<2>(DesignSort[DesignSort.size()-1]) <<  endl;
//    //signal brat z toho tuplu
//    do
//    {
////        cout << rowsLeft << endl;
//        if(rowsLeft > blockSize)
//        {
//            /* We will write to a dense submatrix directly from the DesignSort tuple. */
//            DesignCompSub_mDens = gsl_matrix_alloc(blockSize, moleculeCount);
//            
//            rowIndex2 = 0;
//                    
////            cout << elementIndex << endl;
//            for(int i = elementIndex; rowIndex2 < blockSize; i++)
//            {
//                cout << get<1>(DesignSort[i]) << " " << get<2>(DesignSort[i]) << endl;
//                gsl_matrix_set(DesignCompSub_mDens, rowIndex2, get<1>(DesignSort[i]), get<2>(DesignSort[i]));
//                
//                if(get<0>(DesignSort[i]) != get<0>(DesignSort[i + 1])) rowIndex2++;
//                
//                elementIndex++;
//            }
////            cout << rowIndex2 << endl;
//            
//            /* Cut the vector accordingly */
//            SignalSub_v = gsl_vector_alloc(rowIndex2);
//            
//            for(int i = 0; i < rowIndex2; i++)
//            {
//                cout << i + blockSize * blockIndex << " " << get<1>(MassSigMaskTuple[i + blockSize * blockIndex]) << endl;
//                gsl_vector_set(SignalSub_v, i, get<1>(MassSigMaskTuple[i + blockSize * blockIndex]));
////                cout << gsl_vector_get(SignalSub_v, i) << endl;
//            }
////            cout << endl;
//            DesignCompSubStd_m = gsl_matrix_alloc(DesignCompSub_mDens->size1, DesignCompSub_mDens->size2);
//            SignalSubStd_v = gsl_vector_alloc(SignalSub_v->size);
//            
////            elementIndex += blockSize;
//            rowsLeft -= blockSize;
//        }
//        else
//        {
//            DesignCompSub_mDens = gsl_matrix_alloc(rowsLeft, moleculeCount);
//            
//            rowIndex2 = 0;
//                    
////            cout << elementIndex << endl;
//            for(int i = elementIndex; rowIndex2 < rowsLeft; i++)
//            {
////                cout << get<2>(DesignSort[i]) << endl;
////                cout << get<1>(DesignSort[i]) << " " << get<2>(DesignSort[i]) << endl;
//                gsl_matrix_set(DesignCompSub_mDens, rowIndex2, get<1>(DesignSort[i]), get<2>(DesignSort[i]));
//                
//                if(get<0>(DesignSort[i]) != get<0>(DesignSort[i + 1])) rowIndex2++;
//            }
//            
//            /* Cut the vector accordingly */
//            SignalSub_v = gsl_vector_alloc(rowIndex2);
//            
//            for(int i = 0; i < rowIndex2; i++)
//            {
////                cout << i + blockSize * blockIndex << endl;
////                cout << i + blockSize * blockIndex << " " << get<1>(MassSigMaskTuple[i + blockSize * blockIndex]) << endl;
//                gsl_vector_set(SignalSub_v, i, get<1>(MassSigMaskTuple[i + blockSize * blockIndex]));                
//            }
//            
//            DesignCompSubStd_m = gsl_matrix_alloc(DesignCompSub_mDens->size1, DesignCompSub_mDens->size2);
//            SignalSubStd_v = gsl_vector_alloc(SignalSub_v->size);          
//            
//            elementIndex += rowIndex2;
//            rowsLeft = 0;
//        }
//        
////        ofstream loadedmatrix;
////        loadedmatrix.open("loadedmatrix");
////
////        for (int i = 0; i < DesignCompSub_mDens->size1; i++)
////        {
////            for (int j = 0; j < DesignCompSub_mDens->size2; j++)
////            {
////                loadedmatrix << gsl_matrix_get(DesignCompSub_mDens, i ,j) << " ";
////            }
////            loadedmatrix << endl;
////        }
////        loadedmatrix.close();
//        
////        char* gue[1] = {"%f"};
////        mtrx = fopen("loadedvector", "w");
////        gsl_vector_fprintf(mtrx, SignalSub_v, *gue);
////        fclose(mtrx);
//        
//        /* Transform to standard form */
//        gsl_multilarge_linear_stdform1(Regularization_v, DesignCompSub_mDens, SignalSub_v, DesignCompSubStd_m, SignalSubStd_v, WrkSpc);
//            
//        /* Add the block to the solver */
//        gsl_multilarge_linear_accumulate(DesignCompSubStd_m, SignalSubStd_v, WrkSpc);
//        
//        gsl_matrix_free(DesignCompSub_mDens);
//        gsl_matrix_free(DesignCompSubStd_m);
//        gsl_vector_free(SignalSub_v);
//        gsl_vector_free(SignalSubStd_v);
//        
////        cout << blockIndex << endl;
//        blockIndex++;       
//    }while(rowsLeft > 0);
    
//===============

/* finds out how many CPUs are there. on Linux. */
//    int numCPU = sysconf(_SC_NPROCESSORS_ONLN);
//    cout << numCPU << endl;