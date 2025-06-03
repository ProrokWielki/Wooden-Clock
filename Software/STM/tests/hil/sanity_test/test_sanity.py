def test_register(expectations):
    assert len(expectations) == 1 
        
    for output in expectations:
        expectation_line = output[0]
        lhs = output[1][0]
        rhs = output[1][1]
        
        assert lhs == rhs, f"{expectation_line} expected {lhs} == {rhs}"
