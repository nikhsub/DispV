import numpy as np
import itertools
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras.layers import Dense, Dropout, Flatten,Concatenate, Lambda, Convolution2D, LSTM, Convolution1D, Conv2D,GlobalAveragePooling1D, GlobalMaxPooling1D,TimeDistributed, Flatten
from tensorflow.keras.models import Model
from tensorflow.keras.layers import BatchNormalization


def CNN_block(svs, trks, dropoutRate=0.1, momentum=0.6):


    svs = Convolution1D(64, 1, kernel_initializer='lecun_uniform',  activation='relu', name='sv_conv0')(svs)
    svs = BatchNormalization(momentum=momentum, name="svs_batchnorm0")(svs)
    svs = Dropout(dropoutRate,name='vtx_dropout0')(svs)    
     
    svs = Convolution1D(32, 1, kernel_initializer='lecun_uniform',  activation='relu', name='sv_conv1')(svs)
    svs = BatchNormalization(momentum=momentum, name="svs_batchnorm1")(svs)
    svs = Dropout(dropoutRate,name='vtx_dropout1')(svs)   
 
    svs = Convolution1D(32, 1, kernel_initializer='lecun_uniform',  activation='relu', name='sv_conv2')(svs)
    svs = BatchNormalization(momentum=momentum, name="svs_batchnorm2")(svs)
    svs = Dropout(dropoutRate,name='vtx_dropout2')(svs)  
 
    svs = Convolution1D(8, 1, kernel_initializer='lecun_uniform',  activation='relu', name='sv_conv3')(svs)
    svs = BatchNormalization(momentum=momentum, name="svs_batchnorm3")(svs)
    svs = Dropout(dropoutRate,name='vtx_dropout3')(svs)  

    
    trks = Convolution1D(64, 1, kernel_initializer='lecun_uniform',  activation='relu', name='trk_conv0')(trks)
    trks = BatchNormalization(momentum=momentum, name="trks_batchnorm0")(trks)
    trks = Dropout(dropoutRate,name='trk_dropout0')(trks)    

     
    trks = Convolution1D(32, 1, kernel_initializer='lecun_uniform',  activation='relu', name='trk_conv1')(trks)
    trks = BatchNormalization(momentum=momentum, name="trks_batchnorm1")(trks)
    trks = Dropout(dropoutRate,name='trk_dropout1')(trks)    

    trks = Convolution1D(32, 1, kernel_initializer='lecun_uniform',  activation='relu', name='trk_conv2')(trks)
    trks = BatchNormalization(momentum=momentum, name="trks_batchnorm2")(trks)
    trks = Dropout(dropoutRate,name='trk_dropout2')(trks)    
    
    trks = Convolution1D(8, 1, kernel_initializer='lecun_uniform',  activation='relu', name='trk_conv3')(trks)
    trks = BatchNormalization(momentum=momentum, name="trks_batchnorm3")(trks)
    trks = Dropout(dropoutRate,name='trk_dropout3')(trks)    

    return svs, trks

def CNN_ptrk_block(ptrks, dropoutRate=0.1, momentum=0.6):


    #svs = Convolution1D(64, 1, kernel_initializer='lecun_uniform',  activation='relu', name='sv_conv0')(svs)
    #svs = BatchNormalization(momentum=momentum, name="svs_batchnorm0")(svs)
    #svs = Dropout(dropoutRate,name='vtx_dropout0')(svs)    
    # 
    #svs = Convolution1D(32, 1, kernel_initializer='lecun_uniform',  activation='relu', name='sv_conv1')(svs)
    #svs = BatchNormalization(momentum=momentum, name="svs_batchnorm1")(svs)
    #svs = Dropout(dropoutRate,name='vtx_dropout1')(svs)   
 
    #svs = Convolution1D(32, 1, kernel_initializer='lecun_uniform',  activation='relu', name='sv_conv2')(svs)
    #svs = BatchNormalization(momentum=momentum, name="svs_batchnorm2")(svs)
    #svs = Dropout(dropoutRate,name='vtx_dropout2')(svs)  
 
    #svs = Convolution1D(8, 1, kernel_initializer='lecun_uniform',  activation='relu', name='sv_conv3')(svs)
    #svs = BatchNormalization(momentum=momentum, name="svs_batchnorm3")(svs)
    #svs = Dropout(dropoutRate,name='vtx_dropout3')(svs)  

    
    ptrks = Convolution1D(64, 1, kernel_initializer='lecun_uniform',  activation='relu', name='trk_conv0')(ptrks)
    ptrks = BatchNormalization(momentum=momentum, name="trks_batchnorm0")(ptrks)
    ptrks = Dropout(dropoutRate,name='trk_dropout0')(ptrks)    

   
    ptrks = Convolution1D(32, 1, kernel_initializer='lecun_uniform',  activation='relu', name='trk_conv1')(ptrks)
    ptrks = BatchNormalization(momentum=momentum, name="trks_batchnorm1")(ptrks)
    ptrks = Dropout(dropoutRate,name='trk_dropout1')(ptrks)    

    ptrks = Convolution1D(32, 1, kernel_initializer='lecun_uniform',  activation='relu', name='trk_conv2')(ptrks)
    ptrks = BatchNormalization(momentum=momentum, name="trks_batchnorm2")(ptrks)
    ptrks = Dropout(dropoutRate,name='trk_dropout2')(ptrks)    
    
    ptrks = Convolution1D(8, 1, kernel_initializer='lecun_uniform',  activation='relu', name='trk_conv3')(ptrks)
    ptrks = BatchNormalization(momentum=momentum, name="trks_batchnorm3")(ptrks)
    ptrks = Dropout(dropoutRate,name='trk_dropout3')(ptrks)    

    return ptrks


def GNN_block_knn(svs, trks, trktosv, dropoutRate=0.1, momentum=0.6, ntrk=30, nsv=6, ktrk=15, ksv=3, maxtrk=30):

    trk_center_tt = tf.tile(tf.expand_dims(trks, axis=2), (1, 1, ntrk-1, 1))
    trk_center_tv = tf.tile(tf.expand_dims(trks, axis=2), (1, 1, ksv, 1))
    sv_center_vt  = tf.tile(tf.expand_dims(svs, axis=2), (1, 1, ktrk, 1))
    #sv_center_tv  = tf.tile(tf.expand_dims(svs, axis=2), (1, 1, ntrk, 1))

    trkj_indices = np.zeros((ntrk, ntrk-1))
    for r in range(ntrk):
        for s in range(ntrk-1):
            if r>s:
                trkj_indices[r, s] = s
            if r<=s:
                trkj_indices[r, s] = s+1
    trkj_idx = tf.convert_to_tensor(trkj_indices, dtype=tf.int32)
    trkj_features = tf.gather(trks, trkj_idx, axis=1)
    

    vtedges_indices = np.zeros((nsv, ntrk)) #for vertex center
    for r in range(nsv):
        for s in range(ntrk):
            vtedges_indices[r, s] = int(r*maxtrk)+s

    vtedge_idx = tf.convert_to_tensor(vtedges_indices, dtype=tf.int32)
    vtedge_features = tf.gather(trktosv, vtedge_idx, axis=1)

    vt_tanhipsig = vtedge_features[:,:,:,2]  #tanh(IP3D_sig) for track to vertex
    _, Knn_indices = tf.math.top_k(-vt_tanhipsig, ktrk)
    Knn_indices = tf.expand_dims(Knn_indices, axis=3)

    shape = tf.shape(trks)
    batch_size = shape[0]
    batch_indices = tf.tile(tf.reshape(tf.range(batch_size), (-1, 1, 1, 1)), (1, nsv, ktrk, 1))
    indices = tf.concat([batch_indices, Knn_indices], axis=3)
    trk_knn = tf.gather_nd(trks, indices)

    sv_idx = tf.range(nsv)
    sv_idx = tf.tile(tf.reshape(sv_idx, (1, -1)), (batch_size, 1))
    sv_idx = tf.expand_dims(sv_idx, axis=2)
    batch_idx = tf.range(batch_size)
    batch_idx = tf.tile(tf.reshape(batch_idx, (-1, 1)), (1, nsv))
    batch_idx = tf.expand_dims(batch_idx, axis=2)
    batch_sv = tf.concat([batch_idx, sv_idx], axis=2)
    batch_sv = tf.tile(tf.expand_dims(batch_sv, axis=2), (1, 1, ktrk, 1))
    vt_Knn_indices = tf.concat([batch_sv, Knn_indices], axis=3)
   
    vt_edge_knn = tf.gather_nd(vtedge_features, vt_Knn_indices)
    
 
    print(indices)
    print(trk_knn)

    tvedges_indices = np.zeros((ntrk, nsv)) #for track center
    for r in range(ntrk):
        for s in range(nsv):
            tvedges_indices[r, s]=int(r*ntrk)+s
    tvedge_idx = tf.convert_to_tensor(tvedges_indices, dtype=tf.int32)
    tvedge_features = tf.gather(trktosv, tvedge_idx, axis=1)

    tv_tanhip3d = tvedge_features[:,:,:,1]
    _, Knnsv_indices = tf.math.top_k(-tv_tanhip3d, ksv)
    Knnsv_indices = tf.expand_dims(Knnsv_indices, axis=3)
    
    batch_indices = tf.tile(tf.reshape(tf.range(batch_size), (-1, 1, 1, 1)), (1, ntrk, ksv, 1))
    indices = tf.concat([batch_indices, Knnsv_indices], axis=3)
    sv_knn = tf.gather_nd(svs, indices)

    trk_idx = tf.range(ntrk)
    trk_idx = tf.tile(tf.reshape(trk_idx, (1, -1)), (batch_size, 1))
    trk_idx = tf.expand_dims(trk_idx, axis=2)
    batch_idx = tf.range(batch_size)
    batch_idx = tf.tile(tf.reshape(batch_idx, (-1, 1)), (1, ntrk))
    batch_idx = tf.expand_dims(batch_idx, axis=2)
    batch_trk = tf.concat([batch_idx, trk_idx], axis=2)
    batch_trk = tf.tile(tf.expand_dims(batch_trk, axis=2), (1, 1, ksv, 1))
    tv_Knn_indices = tf.concat([batch_trk, Knnsv_indices], axis=3)
    tv_edge_knn = tf.gather_nd(tvedge_features, tv_Knn_indices)


    Int_tt = tf.concat([trk_center_tt, trkj_features], axis=3)

    Int_vt = tf.concat([sv_center_vt, trk_knn, vt_edge_knn], axis=3)

    Int_tv = tf.concat([trk_center_tv, sv_knn, tv_edge_knn], axis=3) 

    Evt = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Int_vt)
    Evt = BatchNormalization(momentum=momentum)(Evt)
    Evt = Dropout(dropoutRate)(Evt)

    Evt = Dense(32, activation="relu", kernel_initializer='lecun_uniform')(Evt)
    Evt = BatchNormalization(momentum=momentum)(Evt)
    Evt = Dropout(dropoutRate)(Evt)

    Evt = Dense(32, activation="relu", kernel_initializer='lecun_uniform')(Evt)
    Evt = BatchNormalization(momentum=momentum)(Evt)
    Evt = Dropout(dropoutRate)(Evt)

    Evt = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Evt)
    Evt = BatchNormalization(momentum=momentum)(Evt)
    Evt = Dropout(dropoutRate)(Evt)

    Etv = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Int_tv)
    Etv = BatchNormalization(momentum=momentum)(Etv)
    Etv = Dropout(dropoutRate)(Etv)

    Etv = Dense(32, activation="relu", kernel_initializer='lecun_uniform')(Etv)
    Etv = BatchNormalization(momentum=momentum)(Etv)
    Etv = Dropout(dropoutRate)(Etv)

    Etv = Dense(32, activation="relu", kernel_initializer='lecun_uniform')(Etv)
    Etv = BatchNormalization(momentum=momentum)(Etv)
    Etv = Dropout(dropoutRate)(Etv)

    Etv = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Etv)
    Etv = BatchNormalization(momentum=momentum)(Etv)
    Etv = Dropout(dropoutRate)(Etv)

    Evt_vtx = tf.math.reduce_sum(Evt, axis=2)

    Etv_trk = tf.math.reduce_sum(Etv, axis=2)

    Ft = tf.concat([trks, Etv_trk], axis=2)

    Fv = tf.concat([svs, Evt_vtx], axis=2)

    Ft = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    Ft = Dense(32, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    Ft = Dense(32, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    Ft = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    Fv = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Fv)
    Fv = BatchNormalization(momentum=momentum)(Fv)
    Fv = Dropout(dropoutRate)(Fv)

    Fv = Dense(32, activation="relu", kernel_initializer='lecun_uniform')(Fv)
    Fv = BatchNormalization(momentum=momentum)(Fv)
    Fv = Dropout(dropoutRate)(Fv)

    Fv = Dense(32, activation="relu", kernel_initializer='lecun_uniform')(Fv)
    Fv = BatchNormalization(momentum=momentum)(Fv)
    Fv = Dropout(dropoutRate)(Fv)

    Fv = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Fv)
    Fv = BatchNormalization(momentum=momentum)(Fv)
    Fv = Dropout(dropoutRate)(Fv)

    return Fv, Ft

def GNN_block_shallow(svs, trks, trktosv, dropoutRate=0.1, momentum=0.6, ntrk=30, nsv=6, maxtrk=30):

    #trk_center_tt = tf.tile(tf.expand_dims(trks, axis=2), (1, 1, 20, 1))
    trk_center_tt = tf.tile(tf.expand_dims(trks, axis=2), (1, 1, ntrk-1, 1))
    trk_center_tv = tf.tile(tf.expand_dims(trks, axis=1), (1, nsv, 1, 1))
    sv_center_vt  = tf.tile(tf.expand_dims(svs, axis=2), (1, 1, ntrk, 1))

    trkj_indices = np.zeros((ntrk, ntrk-1))
    for r in range(ntrk):
        for s in range(ntrk-1):
            if r>s:
                trkj_indices[r, s] = s
            if r<=s:
                trkj_indices[r, s] = s+1
    trkj_idx = tf.convert_to_tensor(trkj_indices, dtype=tf.int32)
    trkj_features = tf.gather(trks, trkj_idx, axis=1)

    vtedges_indices = np.zeros((nsv, ntrk)) #for vertex center
    for r in range(nsv):
        for s in range(ntrk):
            vtedges_indices[r, s] = int(r*maxtrk)+s

    vtedge_idx = tf.convert_to_tensor(vtedges_indices, dtype=tf.int32)
    vtedge_features = tf.gather(trktosv, vtedge_idx, axis=1)


    Int_tt = tf.concat([trk_center_tt, trkj_features], axis=3)
    
    Ett = Dense(72, activation="relu", kernel_initializer='lecun_uniform')(Int_tt)
    Ett = BatchNormalization(momentum=momentum)(Ett)
    Ett = Dropout(dropoutRate)(Ett)
    
    #Ett = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Ett)
    #Ett = BatchNormalization(momentum=momentum)(Ett)
    #Ett = Dropout(dropoutRate)(Ett)
    
    Ett = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Ett)
    Ett = BatchNormalization(momentum=momentum)(Ett)
    Ett = Dropout(dropoutRate)(Ett)
    
    Ett = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Ett)
    Ett = BatchNormalization(momentum=momentum)(Ett)
    Ett = Dropout(dropoutRate)(Ett)
    

    Int_vt = tf.concat([sv_center_vt, trk_center_tv, vtedge_features], axis=3)

    Evt = Dense(72, activation="relu", kernel_initializer='lecun_uniform')(Int_vt)
    Evt = BatchNormalization(momentum=momentum)(Evt)
    Evt = Dropout(dropoutRate)(Evt)

    #Evt = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Evt)
    #Evt = BatchNormalization(momentum=momentum)(Evt)
    #Evt = Dropout(dropoutRate)(Evt)

    Evt = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Evt)
    Evt = BatchNormalization(momentum=momentum)(Evt)
    Evt = Dropout(dropoutRate)(Evt)

    Evt = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Evt)
    Evt = BatchNormalization(momentum=momentum)(Evt)
    Evt = Dropout(dropoutRate)(Evt)

    Etv = Dense(72, activation="relu", kernel_initializer='lecun_uniform')(Int_vt)
    Etv = BatchNormalization(momentum=momentum)(Etv)
    Etv = Dropout(dropoutRate)(Etv)

    #Etv = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Etv)
    #Etv = BatchNormalization(momentum=momentum)(Etv)
    #Etv = Dropout(dropoutRate)(Etv)

    Etv = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Etv)
    Etv = BatchNormalization(momentum=momentum)(Etv)
    Etv = Dropout(dropoutRate)(Etv)

    Etv = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Etv)
    Etv = BatchNormalization(momentum=momentum)(Etv)
    Etv = Dropout(dropoutRate)(Etv)

    Evt_vtx = tf.math.reduce_sum(Evt, axis=2)

    Etv_trk = tf.math.reduce_sum(Etv, axis=1)

    Ett_trk = tf.math.reduce_sum(Ett, axis=2)

    Ft = tf.concat([trks, Ett_trk, Etv_trk], axis=2)

    Fv = tf.concat([svs, Evt_vtx], axis=2)

    Ft = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    Ft = Dense(32, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    Ft = Dense(32, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    Ft = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    Fv = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Fv)
    Fv = BatchNormalization(momentum=momentum)(Fv)
    Fv = Dropout(dropoutRate)(Fv)

    Fv = Dense(32, activation="relu", kernel_initializer='lecun_uniform')(Fv)
    Fv = BatchNormalization(momentum=momentum)(Fv)
    Fv = Dropout(dropoutRate)(Fv)

    Fv = Dense(32, activation="relu", kernel_initializer='lecun_uniform')(Fv)
    Fv = BatchNormalization(momentum=momentum)(Fv)
    Fv = Dropout(dropoutRate)(Fv)

    Fv = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Fv)
    Fv = BatchNormalization(momentum=momentum)(Fv)
    Fv = Dropout(dropoutRate)(Fv)

    return Fv, Ft






def GNN_block(svs, trks, trktosv, dropoutRate=0.1, momentum=0.6, ntrk=30, nsv=6, maxtrk=30):

    #trk_center_tt = tf.tile(tf.expand_dims(trks, axis=2), (1, 1, 20, 1))
    trk_center_tt = tf.tile(tf.expand_dims(trks, axis=2), (1, 1, ntrk-1, 1))
    trk_center_tv = tf.tile(tf.expand_dims(trks, axis=1), (1, nsv, 1, 1))
    sv_center_vt  = tf.tile(tf.expand_dims(svs, axis=2), (1, 1, ntrk, 1))

    trkj_indices = np.zeros((ntrk, ntrk-1))
    for r in range(ntrk):
        for s in range(ntrk-1):
            if r>s:
                trkj_indices[r, s] = s
            if r<=s:
                trkj_indices[r, s] = s+1
    trkj_idx = tf.convert_to_tensor(trkj_indices, dtype=tf.int32)
    trkj_features = tf.gather(trks, trkj_idx, axis=1)

    vtedges_indices = np.zeros((nsv, ntrk)) #for vertex center
    for r in range(nsv):
        for s in range(ntrk):
            vtedges_indices[r, s] = int(r*maxtrk)+s

    vtedge_idx = tf.convert_to_tensor(vtedges_indices, dtype=tf.int32)
    vtedge_features = tf.gather(trktosv, vtedge_idx, axis=1)


    Int_tt = tf.concat([trk_center_tt, trkj_features], axis=3)
    
    Ett = Dense(100, activation="relu", kernel_initializer='lecun_uniform')(Int_tt)
    Ett = BatchNormalization(momentum=momentum)(Ett)
    Ett = Dropout(dropoutRate)(Ett)
    
    Ett = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Ett)
    Ett = BatchNormalization(momentum=momentum)(Ett)
    Ett = Dropout(dropoutRate)(Ett)
    
    Ett = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Ett)
    Ett = BatchNormalization(momentum=momentum)(Ett)
    Ett = Dropout(dropoutRate)(Ett)
    
    Ett = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Ett)
    Ett = BatchNormalization(momentum=momentum)(Ett)
    Ett = Dropout(dropoutRate)(Ett)
    

    Int_vt = tf.concat([sv_center_vt, trk_center_tv, vtedge_features], axis=3)

    Evt = Dense(100, activation="relu", kernel_initializer='lecun_uniform')(Int_vt)
    Evt = BatchNormalization(momentum=momentum)(Evt)
    Evt = Dropout(dropoutRate)(Evt)

    Evt = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Evt)
    Evt = BatchNormalization(momentum=momentum)(Evt)
    Evt = Dropout(dropoutRate)(Evt)

    Evt = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Evt)
    Evt = BatchNormalization(momentum=momentum)(Evt)
    Evt = Dropout(dropoutRate)(Evt)

    Evt = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Evt)
    Evt = BatchNormalization(momentum=momentum)(Evt)
    Evt = Dropout(dropoutRate)(Evt)

    Etv = Dense(100, activation="relu", kernel_initializer='lecun_uniform')(Int_vt)
    Etv = BatchNormalization(momentum=momentum)(Etv)
    Etv = Dropout(dropoutRate)(Etv)

    Etv = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Etv)
    Etv = BatchNormalization(momentum=momentum)(Etv)
    Etv = Dropout(dropoutRate)(Etv)

    Etv = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Etv)
    Etv = BatchNormalization(momentum=momentum)(Etv)
    Etv = Dropout(dropoutRate)(Etv)

    Etv = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Etv)
    Etv = BatchNormalization(momentum=momentum)(Etv)
    Etv = Dropout(dropoutRate)(Etv)

    Evt_vtx = tf.math.reduce_sum(Evt, axis=2)

    Etv_trk = tf.math.reduce_sum(Etv, axis=1)

    Ett_trk = tf.math.reduce_sum(Ett, axis=2)

    Ft = tf.concat([trks, Ett_trk, Etv_trk], axis=2)

    Fv = tf.concat([svs, Evt_vtx], axis=2)

    Ft = Dense(76, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    Ft = Dense(32, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    Ft = Dense(32, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    Ft = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    Fv = Dense(76, activation="relu", kernel_initializer='lecun_uniform')(Fv)
    Fv = BatchNormalization(momentum=momentum)(Fv)
    Fv = Dropout(dropoutRate)(Fv)

    Fv = Dense(32, activation="relu", kernel_initializer='lecun_uniform')(Fv)
    Fv = BatchNormalization(momentum=momentum)(Fv)
    Fv = Dropout(dropoutRate)(Fv)

    Fv = Dense(32, activation="relu", kernel_initializer='lecun_uniform')(Fv)
    Fv = BatchNormalization(momentum=momentum)(Fv)
    Fv = Dropout(dropoutRate)(Fv)

    Fv = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Fv)
    Fv = BatchNormalization(momentum=momentum)(Fv)
    Fv = Dropout(dropoutRate)(Fv)

    return Fv, Ft

def GNN_block_gated(svs, trks, trktosv, dropoutRate=0.1, momentum=0.6, ntrk=30, nsv=6, maxtrk=30):

    #trk_center_tt = tf.tile(tf.expand_dims(trks, axis=2), (1, 1, 20, 1))
    trk_center_tt = tf.tile(tf.expand_dims(trks, axis=2), (1, 1, ntrk-1, 1))
    trk_center_tv = tf.tile(tf.expand_dims(trks, axis=1), (1, nsv, 1, 1))
    sv_center_vt  = tf.tile(tf.expand_dims(svs, axis=2), (1, 1, ntrk, 1))

    trkj_indices = np.zeros((ntrk, ntrk-1))
    for r in range(ntrk):
        for s in range(ntrk-1):
            if r>s:
                trkj_indices[r, s] = s
            if r<=s:
                trkj_indices[r, s] = s+1
    trkj_idx = tf.convert_to_tensor(trkj_indices, dtype=tf.int32)
    trkj_features = tf.gather(trks, trkj_idx, axis=1)

    vtedges_indices = np.zeros((nsv, ntrk)) #for vertex center
    for r in range(nsv):
        for s in range(ntrk):
            vtedges_indices[r, s] = int(r*maxtrk)+s

    vtedge_idx = tf.convert_to_tensor(vtedges_indices, dtype=tf.int32)
    vtedge_features = tf.gather(trktosv, vtedge_idx, axis=1)


    Int_tt = tf.concat([trk_center_tt, trkj_features], axis=3)
    
    Ett = Dense(100, activation="relu", kernel_initializer='lecun_uniform')(Int_tt)
    Ett = BatchNormalization(momentum=momentum)(Ett)
    Ett = Dropout(dropoutRate)(Ett)
    
    Ett = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Ett)
    Ett = BatchNormalization(momentum=momentum)(Ett)
    Ett = Dropout(dropoutRate)(Ett)
    
    Ett = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Ett)
    Ett = BatchNormalization(momentum=momentum)(Ett)
    Ett = Dropout(dropoutRate)(Ett)
    
    Ett = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Ett)
    Ett = BatchNormalization(momentum=momentum)(Ett)
    Ett = Dropout(dropoutRate)(Ett)

    wtt = Dense(1, activation="sigmoid", kernel_initializer='lecun_uniform')(Ett)
    wtt = BatchNormalization(momentum=momentum)(wtt)
    wtt = Dropout(dropoutRate)(wtt)
    print(tf.shape(wtt))
    wtt_shape = tf.shape(wtt)
    wtt = tf.reshape(wtt, (-1, wtt_shape[1], wtt_shape[2]))

    Ett = tf.transpose(Ett, [3, 0, 1, 2])
    print(tf.shape(Ett))
    print(tf.shape(wtt)) 
    Ett = Ett*wtt
    print(tf.shape(Ett))
    Ett = tf.transpose(Ett, [1, 2, 3, 0])
    

    Int_vt = tf.concat([sv_center_vt, trk_center_tv, vtedge_features], axis=3)

    Evt = Dense(100, activation="relu", kernel_initializer='lecun_uniform')(Int_vt)
    Evt = BatchNormalization(momentum=momentum)(Evt)
    Evt = Dropout(dropoutRate)(Evt)

    Evt = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Evt)
    Evt = BatchNormalization(momentum=momentum)(Evt)
    Evt = Dropout(dropoutRate)(Evt)

    Evt = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Evt)
    Evt = BatchNormalization(momentum=momentum)(Evt)
    Evt = Dropout(dropoutRate)(Evt)

    wvt = Dense(1, activation="sigmoid", kernel_initializer='lecun_uniform')(Evt)
    wvt = BatchNormalization(momentum=momentum)(wvt)
    wvt = Dropout(dropoutRate)(wvt)
    
    wvt_shape = tf.shape(wvt)
    wvt = tf.reshape(wvt, (-1, wvt_shape[1], wvt_shape[2]))
    
    Evt = tf.transpose(Evt, [3, 0, 1, 2])
    Evt = Evt*wvt
    Evt = tf.transpose(Evt, [1, 2, 3, 0])
   
    

    Evt = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Evt)
    Evt = BatchNormalization(momentum=momentum)(Evt)
    Evt = Dropout(dropoutRate)(Evt)

    Etv = Dense(100, activation="relu", kernel_initializer='lecun_uniform')(Int_vt)
    Etv = BatchNormalization(momentum=momentum)(Etv)
    Etv = Dropout(dropoutRate)(Etv)

    Etv = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Etv)
    Etv = BatchNormalization(momentum=momentum)(Etv)
    Etv = Dropout(dropoutRate)(Etv)

    Etv = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Etv)
    Etv = BatchNormalization(momentum=momentum)(Etv)
    Etv = Dropout(dropoutRate)(Etv)

    Etv = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Etv)
    Etv = BatchNormalization(momentum=momentum)(Etv)
    Etv = Dropout(dropoutRate)(Etv)

    wtv = Dense(1, activation="sigmoid", kernel_initializer='lecun_uniform')(Etv)
    wtv = BatchNormalization(momentum=momentum)(wtv)
    wtv = Dropout(dropoutRate)(wtv)
    
    wtv_shape = tf.shape(wtv)
    wtv = tf.reshape(wvt, (-1, wvt_shape[1], wvt_shape[2]))
    
    Etv = tf.transpose(Etv, [3, 0, 1, 2])
    Etv = Etv*wtv
    Etv = tf.transpose(Etv, [1, 2, 3, 0])


    Evt_vtx = tf.math.reduce_sum(Evt, axis=2)

    Etv_trk = tf.math.reduce_sum(Etv, axis=1)

    Ett_trk = tf.math.reduce_sum(Ett, axis=2)

    Ft = tf.concat([trks, Ett_trk, Etv_trk], axis=2)

    Fv = tf.concat([svs, Evt_vtx], axis=2)

    Ft = Dense(76, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    Ft = Dense(32, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    Ft = Dense(32, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    Ft = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    Fv = Dense(76, activation="relu", kernel_initializer='lecun_uniform')(Fv)
    Fv = BatchNormalization(momentum=momentum)(Fv)
    Fv = Dropout(dropoutRate)(Fv)

    Fv = Dense(32, activation="relu", kernel_initializer='lecun_uniform')(Fv)
    Fv = BatchNormalization(momentum=momentum)(Fv)
    Fv = Dropout(dropoutRate)(Fv)

    Fv = Dense(32, activation="relu", kernel_initializer='lecun_uniform')(Fv)
    Fv = BatchNormalization(momentum=momentum)(Fv)
    Fv = Dropout(dropoutRate)(Fv)

    Fv = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Fv)
    Fv = BatchNormalization(momentum=momentum)(Fv)
    Fv = Dropout(dropoutRate)(Fv)

    return Fv, Ft

def GNN_ptrk_block(ptrks, dropoutRate=0.1, momentum=0.6, nptrk=20):

    ptrk_PVidx = ptrks[:,:,0]
    ptrk_features = ptrks[:,:,1:]
    ptrk_PVidx = tf.expand_dims(ptrk_PVidx, axis=2)
    print(ptrk_PVidx)
    ptrk_center_tt = tf.tile(tf.expand_dims(ptrk_features, axis=2), (1, 1, nptrk-1, 1))
    ptrkPV_center_tt = tf.tile(tf.expand_dims(ptrk_PVidx, axis=2), (1, 1, nptrk-1, 1))
    
    trkj_indices = np.zeros((nptrk, nptrk-1))
    
    for r in range(nptrk):
        for s in range(nptrk-1):
            if r>s:
                trkj_indices[r, s] = s
            if r<=s:
                trkj_indices[r, s] = s+1
    trkj_idx = tf.convert_to_tensor(trkj_indices, dtype=tf.int32)
    trkj_features = tf.gather(ptrk_features, trkj_idx, axis=1)
    trkj_PVidx = tf.gather(ptrk_PVidx, trkj_idx, axis=1)

    trkij_samePV = tf.cast( tf.math.equal(ptrkPV_center_tt, trkj_PVidx),  tf.float32)

    Int_tt = tf.concat([ptrk_center_tt, trkj_features, trkij_samePV], axis=3)

    Ett = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Int_tt)
    Ett = BatchNormalization(momentum=momentum)(Ett)
    Ett = Dropout(dropoutRate)(Ett)

    Ett = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Ett)
    Ett = BatchNormalization(momentum=momentum)(Ett)
    Ett = Dropout(dropoutRate)(Ett)

    Ett = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Ett)
    Ett = BatchNormalization(momentum=momentum)(Ett)
    Ett = Dropout(dropoutRate)(Ett)

    Ett_trk = tf.math.reduce_sum(Ett, axis=2)

    Ft = tf.concat([ptrk_features, Ett_trk], axis=2)

    Ft = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    Ft = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    Ft = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    return Ft
    
def GNN_ptrkslim_block(ptrks, dropoutRate=0.1, momentum=0.6, nptrk=20):

    #ptrk_PVidx = ptrks[:,:,0]
    ptrk_features = ptrks
    #ptrk_PVidx = tf.expand_dims(ptrk_PVidx, axis=2)
    #print(ptrk_PVidx)
    ptrk_center_tt = tf.tile(tf.expand_dims(ptrk_features, axis=2), (1, 1, nptrk-1, 1))
    #ptrkPV_center_tt = tf.tile(tf.expand_dims(ptrk_PVidx, axis=2), (1, 1, nptrk-1, 1))
    
    trkj_indices = np.zeros((nptrk, nptrk-1))
    
    for r in range(nptrk):
        for s in range(nptrk-1):
            if r>s:
                trkj_indices[r, s] = s
            if r<=s:
                trkj_indices[r, s] = s+1
    trkj_idx = tf.convert_to_tensor(trkj_indices, dtype=tf.int32)
    trkj_features = tf.gather(ptrk_features, trkj_idx, axis=1)
    #trkj_PVidx = tf.gather(ptrk_PVidx, trkj_idx, axis=1)

    #trkij_samePV = tf.cast( tf.math.equal(ptrkPV_center_tt, trkj_PVidx),  tf.float32)

    Int_tt = tf.concat([ptrk_center_tt, trkj_features], axis=3)

    Ett = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Int_tt)
    Ett = BatchNormalization(momentum=momentum)(Ett)
    Ett = Dropout(dropoutRate)(Ett)

    Ett = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Ett)
    Ett = BatchNormalization(momentum=momentum)(Ett)
    Ett = Dropout(dropoutRate)(Ett)

    Ett = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Ett)
    Ett = BatchNormalization(momentum=momentum)(Ett)
    Ett = Dropout(dropoutRate)(Ett)

    Ett_trk = tf.math.reduce_sum(Ett, axis=2)

    Ft = tf.concat([ptrk_features, Ett_trk], axis=2)

    Ft = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    Ft = Dense(64, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    Ft = Dense(8, activation="relu", kernel_initializer='lecun_uniform')(Ft)
    Ft = BatchNormalization(momentum=momentum)(Ft)
    Ft = Dropout(dropoutRate)(Ft)

    return Ft
    
