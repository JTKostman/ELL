////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Machine Learning Library (EMLL)
//  File:     InputNode.tcc (model)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary> model namespace </summary>
namespace model
{
    template <typename ValueType>
    InputNode<ValueType>::InputNode() : Node({}, { &_output }), _output(this, outputPortName, 0)
    {};

    template <typename ValueType>
    InputNode<ValueType>::InputNode(size_t dimension) : Node({}, { &_output }), _output(this, outputPortName, dimension){};

    template <typename ValueType>
    void InputNode<ValueType>::SetInput(ValueType inputValue)
    {
        SetInput(std::vector<ValueType>{inputValue});
    }

    template <typename ValueType>
    void InputNode<ValueType>::SetInput(std::vector<ValueType> inputValues)
    {
        assert(_output.Size() == inputValues.size());
        _inputValues = inputValues;
    }

    template <typename ValueType>
    void InputNode<ValueType>::Compute() const
    {
        _output.SetOutput(_inputValues);
    }

    template <typename ValueType>
    void InputNode<ValueType>::Copy(ModelTransformer& transformer) const
    {
        auto newNode = transformer.AddNode<InputNode<ValueType>>(_output.Size());
        transformer.MapNodeOutput(output, newNode->output);
    }

    template <typename ValueType>
    void InputNode<ValueType>::Serialize(utilities::Serializer& serializer) const
    {
        Node::Serialize(serializer);
        serializer.Serialize("output", _output);
    }

    template <typename ValueType>
    void InputNode<ValueType>::Deserialize(utilities::Deserializer& serializer, utilities::SerializationContext& context)
    {
        ModelSerializationContext& newContext = dynamic_cast<ModelSerializationContext&>(context);
        Node::Deserialize(serializer, newContext);
        serializer.Deserialize("output", _output, context);
    }
}
