PROTO_FLAGS = -I../Messages/tools/nanopb/generator/proto -I../Messages/protos/flashing -I../Messages/protos/flashing/detail --python_out=generated_protos
PROTO_FLAGS_DETAIL = -I../Messages/tools/nanopb/generator/proto -I../Messages/protos/flashing/detail --python_out=generated_protos

proto:
	protoc $(PROTO_FLAGS_DETAIL) ../Messages/protos/flashing/detail/*.proto
	protoc $(PROTO_FLAGS) ../Messages/protos/flashing/*.proto
	protoc $(PROTO_FLAGS) ../Messages/tools/nanopb/generator/proto/nanopb.proto
