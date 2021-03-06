// Generated by the protocol buffer compiler.  DO NOT EDIT!

import Foundation

private class UnittestNoGenericServicesRoot {
    private var UnittestNoGenericServicesRoot_testExtension:ConcreteExtensionField<Int32,TestMessage>
    var extensionRegistry:ExtensionRegistry

    init() {
        UnittestNoGenericServicesRoot_testExtension = ConcreteExtensionField(type:ExtensionType.ExtensionTypeInt32, fieldNumber:1000, defaultValue:0, isRepeated:false, isPacked:false, isMessageSetWireFormat:false)
        extensionRegistry = ExtensionRegistry()
        registerAllExtensions(extensionRegistry)
      }
    func registerAllExtensions(registry:ExtensionRegistry) {
      registry.addExtension(UnittestNoGenericServicesRoot_testExtension)
    }
    var testExtension:ExtensionField {
         get {
             return UnittestNoGenericServicesRoot_testExtension
         }
    }
    }

enum TestEnum:Int32 {
  case TestEnumFoo = 1

  static func TestEnumIsValidValue(value:TestEnum) ->Bool {
    switch value {
      case .TestEnumFoo:
        return true;
      default:
        return false;
    }
  }
}

func == (lhs: TestMessage, rhs: TestMessage) -> Bool {
      if (lhs === rhs) {
        return true
      }
      var fieldCheck:Bool = (lhs.hashValue == rhs.hashValue)
      fieldCheck = fieldCheck && (lhs.hasA == rhs.hasA) && (!lhs.hasA || lhs.a == rhs.a)
       fieldCheck = fieldCheck && lhs.isEqualExtensionsInOther(rhs, startInclusive:Int32(1000), endExclusive:Int32(536870912))
       return (fieldCheck && (lhs.unknownFields == rhs.unknownFields))
}
class TestMessage : ExtendableMessage {
  private(set) var hasA:Bool = false
  private(set) var a:Int32 = 0

  override init() {
       super.init()
  }
  override func isInitialized() -> Bool {
    if !extensionsAreInitialized() {
      return false
    }
    return true
  }
  override func writeToCodedOutputStream(output:CodedOutputStream) {
    if hasA {
      output.writeInt32(1, value:a)
    }
    writeExtensionsToCodedOutputStream(output, startInclusive:Int32(1000), endExclusive:Int32(536870912))
    unknownFields.writeToCodedOutputStream(output)
  }
  override func serializedSize() -> Int32 {
    var size:Int32 = memoizedSerializedSize
    if size != -1 {
      return size
    }

    size = 0
    if hasA {
      size += WireFormat.computeInt32Size(1, value:a)
    }
    size += extensionsSerializedSize()
    size += unknownFields.serializedSize()
    memoizedSerializedSize = size
    return size
  }
  class func parseFromData(data:[Byte]) -> TestMessage {
    return TestMessage.builder().mergeFromData(data).build()
  }
  class func parseFromData(data:[Byte], extensionRegistry:ExtensionRegistry) -> TestMessage {
    return TestMessage.builder().mergeFromData(data, extensionRegistry:extensionRegistry).build()
  }
  class func parseFromInputStream(input:NSInputStream) -> TestMessage {
    return TestMessage.builder().mergeFromInputStream(input).build()
  }
  class func parseFromInputStream(input:NSInputStream, extensionRegistry:ExtensionRegistry) ->TestMessage {
    return TestMessage.builder().mergeFromInputStream(input, extensionRegistry:extensionRegistry).build()
  }
  class func parseFromCodedInputStream(input:CodedInputStream) -> TestMessage {
    return TestMessage.builder().mergeFromCodedInputStream(input).build()
  }
  class func parseFromCodedInputStream(input:CodedInputStream, extensionRegistry:ExtensionRegistry) -> TestMessage {
    return TestMessage.builder().mergeFromCodedInputStream(input, extensionRegistry:extensionRegistry).build()
  }
  class func builder() -> TestMessageBuilder {
    return TestMessageBuilder()
  }
  class func builderWithPrototype(prototype:TestMessage) -> TestMessageBuilder {
    return TestMessage.builder().mergeFrom(prototype)
  }
  func builder() -> TestMessageBuilder {
    return TestMessage.builder()
  }
  func toBuilder() -> TestMessageBuilder {
    return TestMessage.builderWithPrototype(self)
  }
  override func writeDescriptionTo(inout output:String, indent:String) {
    if hasA {
      output += "\(indent) a: \(a) \n"
    }
    writeExtensionDescription(&output, startInclusive:Int32(1000), endExclusive:Int32(536870912), indent:indent)
    unknownFields.writeDescriptionTo(&output, indent:indent)
  }
  override var hashValue:Int {
   get {
        var hashCode:Int = 7
        if hasA {
           hashCode = (hashCode &* 31) &+ a.hashValue
        }
        hashCode = (hashCode &* 31) &+ Int(hashExtensionsFrom(Int32(1000), endExclusive:Int32(536870912)))
        hashCode = (hashCode &* 31) &+  unknownFields.hashValue
        return hashCode
      }
    }
  }

  class TestMessageBuilder : ExtendableMessageBuilder {
  private var result:TestMessage

  override init () {
     result = TestMessage()
  }
  var hasA:Bool {
       get {
            return result.hasA
       }
  }
  var a:Int32 {
       get {
            return result.a
       }
       set (value) {
           result.hasA = true
           result.a = value
       }
  }
  func clearA() -> TestMessageBuilder{
       result.hasA = false
       result.a = 0
       return self
  }
  override var internalGetResult:ExtendableMessage {
       get {
           return result
       }
  }
  override func clear() -> TestMessageBuilder {
    result = TestMessage()
    return self
  }
  override func clone() -> TestMessageBuilder {
    return TestMessage.builderWithPrototype(result)
  }
  func build() -> TestMessage {
       checkInitialized()
       return buildPartial()
  }
  func buildPartial() -> TestMessage {
    var returnMe:TestMessage = result
    return returnMe
  }
  func mergeFrom(other:TestMessage) -> TestMessageBuilder {
    if (other == TestMessage()) {
      return self
    }
    if other.hasA {
         a = other.a
    }
    mergeExtensionFields(other)
      mergeUnknownFields(other.unknownFields)
    return self
  }
  override func mergeFromCodedInputStream(input:CodedInputStream) ->TestMessageBuilder {
       return mergeFromCodedInputStream(input, extensionRegistry:ExtensionRegistry())
  }
  override func mergeFromCodedInputStream(input:CodedInputStream, extensionRegistry:ExtensionRegistry) -> TestMessageBuilder {
    var unknownFieldsBuilder:UnknownFieldSetBuilder = UnknownFieldSet.builderWithUnknownFields(self.unknownFields)
    while (true) {
      var tag:Int32 = input.readTag()
        if tag == 0 {
             self.unknownFields = unknownFieldsBuilder.build()
             return self}
        else if tag == 8 {
          a = input.readInt32()
        }
        else {
              if (!parseUnknownField(input,unknownFields:unknownFieldsBuilder, extensionRegistry:extensionRegistry, tag:tag)) {
                  unknownFields = unknownFieldsBuilder.build()
                  return self
              }
        }
        }
     }
  }


  // @@protoc_insertion_point(global_scope)
