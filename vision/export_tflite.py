import torch
def export_to_tflite(input_model="person_detector.pt"):
    model = torch.load(input_model)
    model.eval()
    dummy = torch.randn(1, 3, 224, 224)
    torch.onnx.export(model, dummy, "person_detector.onnx")
    print("Exported to ONNX. Convert with tf_lite_converter.")
