// Protocol Buffers for Swift
//
// Copyright 2014 Alexey Khohklov(AlexeyXo).
// Copyright 2008 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "swift_enum_field.h"

#include <map>
#include <string>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/wire_format.h>
#include <google/protobuf/stubs/strutil.h>

#include "swift_helpers.h"

namespace google { namespace protobuf { namespace compiler { namespace swift {

  namespace {
    void SetEnumVariables(const FieldDescriptor* descriptor,
      map<string, string>* variables) {
        const EnumValueDescriptor* default_value;
        default_value = descriptor->default_value_enum();

        string type = ClassName(descriptor->enum_type());

        (*variables)["classname"]             = ClassName(descriptor->containing_type());
        (*variables)["name"]                  = UnderscoresToCamelCase(descriptor);
        (*variables)["capitalized_name"]      = UnderscoresToCapitalizedCamelCase(descriptor);
//        (*variables)["list_name"]             = UnderscoresToCamelCase(descriptor) + "Array";
        (*variables)["number"] = SimpleItoa(descriptor->number());
        (*variables)["type"] = type;
        (*variables)["default"] = EnumValueName(default_value);
        (*variables)["tag"] = SimpleItoa(internal::WireFormat::MakeTag(descriptor));
        (*variables)["tag_size"] = SimpleItoa(
          internal::WireFormat::TagSize(descriptor->number(), descriptor->type()));
    }
  }  // namespace

  EnumFieldGenerator::EnumFieldGenerator(const FieldDescriptor* descriptor)
    : descriptor_(descriptor) {
      SetEnumVariables(descriptor, &variables_);
  }


  EnumFieldGenerator::~EnumFieldGenerator() {
  }


  void EnumFieldGenerator::GenerateExtensionSource(io::Printer* printer) const {
    printer->Print(variables_,
      "var $name$:$type$\n");
  }

  void EnumFieldGenerator::GenerateMembersSource(io::Printer* printer) const {
  }


  void EnumFieldGenerator::GenerateSynthesizeSource(io::Printer* printer) const {
      printer->Print(variables_, "private(set) var $name$:$type$ = .$default$\n");
      printer->Print(variables_,"private(set) var has$capitalized_name$:Bool = false"
                     "\n");
  }




  void EnumFieldGenerator::GenerateInitializationSource(io::Printer* printer) const {
  }




  void EnumFieldGenerator::GenerateBuilderMembersSource(io::Printer* printer) const {
      printer->Print(variables_,
     "  var has$capitalized_name$:Bool{\n"
     "      get {\n"
     "          return result.has$capitalized_name$\n"
     "      }\n"
     "  }\n"
     "  var $name$:$type$ {\n"
     "      get {\n"
     "          return result.$name$\n"
     "      }\n"
     "      set (value) {\n"
     "          result.has$capitalized_name$ = true\n"
     "          result.$name$ = value\n"
     "      }\n"
     "  }\n");

    printer->Print(variables_,
      "  func clear$capitalized_name$() -> $classname$Builder {\n"
      "     result.has$capitalized_name$ = false\n"
      "     result.$name$ = .$default$\n"
      "     return self\n"
      "  }\n");
  }



  void EnumFieldGenerator::GenerateMergingCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "if other.has$capitalized_name$ {\n"
      "     $name$ = other.$name$\n"
      "}\n");
  }


  void EnumFieldGenerator::GenerateBuildingCodeSource(io::Printer* printer) const {
  }

  void EnumFieldGenerator::GenerateParsingCodeSource(io::Printer* printer) const {
    printer->Print(variables_,

      "var value = input.readEnum()\n"
      "var enums:$type$ = $type$.fromRaw(value)!\n"
      "if ($type$.$type$IsValidValue(enums)) {\n"
      "     $name$ = enums\n"
      "} else {\n"
      "     unknownFieldsBuilder.mergeVarintField($number$, value:Int64(value))\n"
      "}\n");
  }

  void EnumFieldGenerator::GenerateSerializationCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "if has$capitalized_name$ {\n"
      "  output.writeEnum($number$, value:$name$.toRaw())\n"
      "}\n");
  }


  void EnumFieldGenerator::GenerateSerializedSizeCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "if (has$capitalized_name$) {\n"
      "  size += WireFormat.computeEnumSize($number$, value:$name$.toRaw())\n"
      "}\n");
  }


  void EnumFieldGenerator::GenerateDescriptionCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "if (has$capitalized_name$) {\n"
      "  output += \"\\(indent) $name$: \\($name$.toRaw())\\n\"\n"
      "}\n");
  }


  void EnumFieldGenerator::GenerateIsEqualCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "(lhs.has$capitalized_name$ == rhs.has$capitalized_name$) && (!lhs.has$capitalized_name$ || lhs.$name$ == rhs.$name$)");
  }


  void EnumFieldGenerator::GenerateHashCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "if has$capitalized_name$ {\n"
      "   hashCode = (hashCode &* 31) &+ Int($name$.toRaw())\n"
      "}\n");
  }


  string EnumFieldGenerator::GetBoxedType() const {
    return ClassName(descriptor_->enum_type());
  }


  RepeatedEnumFieldGenerator::RepeatedEnumFieldGenerator(const FieldDescriptor* descriptor)
    : descriptor_(descriptor) {
      SetEnumVariables(descriptor, &variables_);
  }


  RepeatedEnumFieldGenerator::~RepeatedEnumFieldGenerator() {
  }



  void RepeatedEnumFieldGenerator::GenerateExtensionSource(io::Printer* printer) const {
      printer->Print(variables_,"var $name$:[$type$] = [$type$]()\n");
  }

  void RepeatedEnumFieldGenerator::GenerateSynthesizeSource(io::Printer* printer) const {
//    printer->Print(variables_, "var $name$:$type$\n");
  }



  void RepeatedEnumFieldGenerator::GenerateInitializationSource(io::Printer* printer) const {
  }

  void RepeatedEnumFieldGenerator::GenerateMembersSource(io::Printer* printer) const {
      printer->Print(variables_,
                     "private var $name$MemoizedSerializedSize:Int32 = 0\n");
    printer->Print(variables_,
      "private(set) var $name$:[$type$] = [$type$]()\n");
  }

  void RepeatedEnumFieldGenerator::GenerateBuilderMembersSource(io::Printer* printer) const {
    printer->Print(variables_,
      "var $name$:[$type$] {\n"
                   "    get {\n"
                   "        return result.$name$\n"
                   "    }\n"
                   "    set (value) {\n"
                   "        result.$name$ += value\n"
                   "    }\n"
      "}\n"
      "func clear$capitalized_name$() -> $classname$Builder {\n"
      "  result.$name$.removeAll(keepCapacity: false)\n"
      "  return self\n"
      "}\n");
  }

  void RepeatedEnumFieldGenerator::GenerateMergingCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "if !other.$name$.isEmpty {\n"
      "   result.$name$ += other.$name$\n"
      "}\n"
      );
  }

  void RepeatedEnumFieldGenerator::GenerateBuildingCodeSource(io::Printer* printer) const {
  }

  void RepeatedEnumFieldGenerator::GenerateParsingCodeSource(io::Printer* printer) const {
    // If packed, set up the while loop
    if (descriptor_->options().packed()) {
      printer->Print(variables_,
        "var length:Int32 = input.readRawVarint32()\n"
        "var oldLimit:Int32 = input.pushLimit(length)\n"
        "while input.bytesUntilLimit() > 0 {\n");
      printer->Indent();
    }

    printer->Print(variables_,
      "var value:$type$ = $type$.fromRaw(input.readEnum())!\n"
      "if $type$.$type$IsValidValue(value) {\n"
      "     result.$name$ += [value]\n"
      "} else {\n"
      "     unknownFieldsBuilder.mergeVarintField($number$, value:Int64(value.toRaw()))\n"
      "}\n");

    if (descriptor_->options().packed()) {
      printer->Outdent();
      printer->Print(variables_,
        "}\n"
        "input.popLimit(oldLimit)\n");
    }
  }

  void RepeatedEnumFieldGenerator::GenerateSerializationCodeSource(io::Printer* printer) const {

    if (descriptor_->options().packed()) {
      printer->Print(variables_,
        "if !$name$.isEmpty {\n"
        "  output.writeRawVarint32($tag$)\n"
        "  output.writeRawVarint32($name$MemoizedSerializedSize)\n"
        "}\n"
        "for value in $name$ {\n"
        "    output.writeEnumNoTag(value.toRaw())\n"
        "}\n");
    } else {
      printer->Print(variables_,
        "for value in $name$ {\n"
        "    output.writeEnum($number$, value:value.toRaw())\n"
        "}\n");
    }
  }


  void RepeatedEnumFieldGenerator::GenerateSerializedSizeCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "  var dataSize$name$:Int32 = 0\n");
    printer->Indent();

    printer->Print(variables_,
      "for value in $name$ {\n"
      "    dataSize$name$ += WireFormat.computeEnumSizeNoTag(value.toRaw())\n"
      "}\n");

    printer->Print(variables_,
      "size += dataSize$name$\n");

    if (descriptor_->options().packed()) {
      printer->Print(variables_,
        "if !$name$.isEmpty {\n"
        "  size += $tag_size$\n"
        "  size += WireFormat.computeRawVarint32Size(dataSize$name$)\n");
    } else {
      printer->Print(variables_,
        "size += ($tag_size$ * Int32($name$.count))\n");
    }

    if (descriptor_->options().packed()) {
      printer->Print(variables_,
        "$name$MemoizedSerializedSize = dataSize$name$\n");
    }

    printer->Outdent();
//    printer->Print("}\n");
  }


  void RepeatedEnumFieldGenerator::GenerateDescriptionCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
    "var $name$ElementIndex:Int = 0\n"
    "for element in $name$ {\n"
    "    output += \"\\(indent) $name$[\\($name$ElementIndex)]: \\(element.toRaw())\"\n"
    "    $name$ElementIndex++\n"
    "}\n");
  }


  void RepeatedEnumFieldGenerator::GenerateIsEqualCodeSource(io::Printer* printer) const {
    printer->Print(variables_, "(lhs.$name$ == rhs.$name$)");
  }


  void RepeatedEnumFieldGenerator::GenerateHashCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
   "for element in $name$ {\n"
   "    hashCode = (hashCode &* 31) &+ Int(element.toRaw())\n"
   "}\n");
  }
}  // namespace swift
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
