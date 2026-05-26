"""Unit tests for person detection module."""
import pytest
import torch
import sys
sys.path.insert(0, "..")

from train_person_detection import create_model


class TestPersonDetection:
    def test_model_creation(self):
        model = create_model(num_classes=2)
        assert model is not None
    
    def test_model_output_shape(self):
        model = create_model(num_classes=2)
        model.eval()
        dummy = torch.randn(1, 3, 224, 224)
        output = model(dummy)
        assert output.shape == (1, 2)
    
    def test_model_parameter_count(self):
        model = create_model(num_classes=2)
        params = sum(p.numel() for p in model.parameters())
        assert params < 5_000_000, f"Model too large: {params:,} params"
    
    def test_model_inference_speed(self):
        import time
        model = create_model(num_classes=2)
        model.eval()
        dummy = torch.randn(1, 3, 224, 224)
        
        start = time.time()
        for _ in range(100):
            with torch.no_grad():
                model(dummy)
        elapsed = time.time() - start
        
        avg_ms = (elapsed / 100) * 1000
        assert avg_ms < 100, f"Inference too slow: {avg_ms:.1f}ms"


class TestFirmwareCompilation:
    def test_platformio_ini_exists(self):
        import os
        assert os.path.exists("../firmware/platformio.ini")
    
    def test_main_cpp_exists(self):
        import os
        assert os.path.exists("../firmware/src/main.cpp")
    
    def test_all_headers_exist(self):
        import os
        headers = [
            "gps_tracker.h", "pid_controller.h",
            "person_detector.h", "rain_sensor.h", "failsafe.h"
        ]
        for h in headers:
            assert os.path.exists(f"../firmware/src/{h}"), f"Missing: {h}"


if __name__ == "__main__":
    pytest.main([__file__, "-v"])
