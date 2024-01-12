import os, sys
import time
import argparse

import tensorflow as tf 
from tensorflow.python.framework import graph_io
from tensorflow.python.tools import freeze_graph

from utils import roc_auc, custom_loss

import tools

from tools import save_graph

def saveCheckpoint(model, outputDirectory = ""):
  #Create saver object to save variables 

  #Save training checkpoint (contains a copy of the model and the weights)
  try:
    os.mkdir(outputDirectory + "models")
  except OSError:
    pass
  checkpoint_path = outputDirectory + "models/model.ckpt"
  checkpoint = tf.train.Checkpoint(model)

  save_path = checkpoint.save(checkpoint_path)#save_path = tf.train.Saver().save(sess, checkpoint_path)

  print("Model checkpoint saved in file: %s" % save_path)



def saveModel(sess, outputDirectory= ""):

    input_graph_path = outputDirectory + "tfModel.pb"
    graph_io.write_graph(sess.graph, "./", input_graph_path)
  
    #create frozen version of graph for distribution
    input_saver_def_path = ""
    input_binary = False
    checkpoint_path = outputDirectory + "models/model.ckpt-1"
    output_node_names = "y_ph/Sigmoid"
    restore_op_name = "save/restore_all"
    filename_tensor_name = "save/Const:0"
    output_graph_path = outputDirectory + "tfModel_frozen.pb"
    clear_devices = False
  
    freeze_graph.freeze_graph(input_graph_path, input_saver_def_path,
                              input_binary, checkpoint_path, output_node_names,
                              restore_op_name, filename_tensor_name,
                              output_graph_path, clear_devices, "")
  
    print("Frozen model (model and weights) saved in file: %s" % output_graph_path)



parser = argparse.ArgumentParser(description="Convert keras model to a constant graph in tensorflow")
parser.add_argument("-i", "--input", default="", help="The path for the input file")
parser.add_argument("-o", "--output", default="", help="The path for the output file")

args = parser.parse_args()

from tensorflow.keras.models import load_model 

custom_objects = {"roc_auc":roc_auc, "custom_loss":custom_loss}


from tensorflow.python.keras import backend as K
from tensorflow import keras

with keras.utils.custom_object_scope(custom_objects):
    model = load_model(args.input)


save_graph("testgraph.pb", model, variables_to_constants=True)
#full_model = tf.function(lambda x: model(x))
#full_model = full_model.get_concrete_function(
#   [tf.TensorSpec(model.inputs[0].shape, model.inputs[0].dtype, name="jet1"), 
#   tf.TensorSpec(model.inputs[1].shape, model.inputs[1].dtype, name="jet2"),
#   tf.TensorSpec(model.inputs[2].shape, model.inputs[2].dtype, name="dijet"),
#   tf.TensorSpec(model.inputs[3].shape, model.inputs[3].dtype, name="sv"), 
#   tf.TensorSpec(model.inputs[4].shape, model.inputs[4].dtype, name="trks"), 
#   tf.TensorSpec(model.inputs[5].shape, model.inputs[5].dtype, name="trktosv")])
#
#from tensorflow.python.framework.convert_to_constants import convert_variables_to_constants_v2
#
#frozen_func = convert_variables_to_constants_v2(full_model)
#
#frozen_func.graph.as_graph_def()
#
#layers = [op.name for op in frozen_func.graph.get_operations()]
#for layer in layers:
#    print(layer)
#print("Frozen model inputs: ", frozen_func.inputs)
#print("Frozen model outputs: ", frozen_func.outputs)
#
#tf.io.write_graph(graph_or_graph_def=frozen_func.graph,
#                  logdir = args.output,
#                  name = "tf_frozen_graph.pb", 
#                  as_text=False)
#
#print(model.inputs)
#K.set_learning_phase(False)
#
#sess = K.get_session()
#saveCheckpoint(model, args.output+"/")
#saveModel(sess, args.output+"/")
