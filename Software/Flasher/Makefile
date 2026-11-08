OUTPUT_DIR = ./generated_protos

NANOPB_PROTO_FLAGS = -I../Messages/tools/nanopb/generator/proto

FLASHING_PROTO_FLAGS = $(NANOPB_PROTO_FLAGS) -I../Messages/protos/flashing -I../Messages/protos/flashing/detail
FLASHING_PROTO_FLAGS_DETAIL = $(NANOPB_PROTO_FLAGS) -I../Messages/protos/flashing/detail

DEBUG_PROTO_FLAGS_DETAIL = $(NANOPB_PROTO_FLAGS) -I../Messages/protos/debug/detail
DEBUG_PROTO_FLAGS = $(NANOPB_PROTO_FLAGS) -I../Messages/protos/debug -I../Messages/protos/debug/detail

NANOPB_PROTO_FLAGS_DETAIL = $(NANOPB_PROTO_FLAGS) -I../Messages/protos/debug/detail

proto:
	protoc $(FLASHING_PROTO_FLAGS_DETAIL) --python_out=$(OUTPUT_DIR) --pyi_out=$(OUTPUT_DIR) ../Messages/protos/flashing/detail/*.proto
	protoc $(FLASHING_PROTO_FLAGS) --python_out=$(OUTPUT_DIR) --pyi_out=$(OUTPUT_DIR) ../Messages/protos/flashing/*.proto
	protoc $(DEBUG_PROTO_FLAGS_DETAIL) --python_out=$(OUTPUT_DIR) --pyi_out=$(OUTPUT_DIR) ../Messages/protos/debug/detail/*.proto
	protoc $(DEBUG_PROTO_FLAGS) --python_out=$(OUTPUT_DIR) --pyi_out=$(OUTPUT_DIR) ../Messages/protos/debug/*.proto
	protoc $(NANOPB_PROTO_FLAGS_DETAIL) --python_out=$(OUTPUT_DIR) --pyi_out=$(OUTPUT_DIR) ../Messages/tools/nanopb/generator/proto/nanopb.proto

format:
	black --config .black .

format-check:
	black --check --config .black .

flake8:
	flake8

