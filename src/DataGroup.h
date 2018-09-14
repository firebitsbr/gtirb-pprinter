//===- DataGroup.h ----------------------------------------------*- C++ -*-===//
//
//  Copyright (C) 2018 GrammaTech, Inc.
//
//  This code is licensed under the MIT license. See the LICENSE file in the
//  project root for license terms.
//
//  This project is sponsored by the Office of Naval Research, One Liberty
//  Center, 875 N. Randolph Street, Arlington, VA 22203 under contract #
//  N68335-17-C-0700.  The content of the information does not necessarily
//  reflect the position or policy of the Government and no official
//  endorsement should be inferred.
//
//===----------------------------------------------------------------------===//
#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "Export.h"

///
/// \class DisasmData
///
/// Port of the prolog disasm.
///
class DEBLOAT_PRETTYPRINTER_EXPORT_API DataGroup {
public:
  enum class Type { LabelMarker, PLTReference, Pointer, PointerDiff, String, RawByte };

  DataGroup() = delete;

  DataGroup(uint64_t x) : ea(x) {}

  virtual ~DataGroup() = default;

  virtual DataGroup::Type getType() const = 0;

  inline void setEA(uint64_t x) { this->ea = x; }

  inline uint64_t getEA() const { return this->ea; }

private:
  uint64_t ea{0};
};

///
/// \class DataGroupLabelMarker
///
class DEBLOAT_PRETTYPRINTER_EXPORT_API DataGroupLabelMarker : public DataGroup {
public:
  DataGroupLabelMarker(uint64_t x) : DataGroup(x) {}

  ~DataGroupLabelMarker() override = default;

  DataGroup::Type getType() const override { return DataGroup::Type::LabelMarker; }

private:
};

///
/// \class DataGroupPLTReference
///
class DEBLOAT_PRETTYPRINTER_EXPORT_API DataGroupPLTReference : public DataGroup {
public:
  DataGroupPLTReference(uint64_t x) : DataGroup(x) {}

  ~DataGroupPLTReference() override = default;

  DataGroup::Type getType() const override { return DataGroup::Type::PLTReference; }

  std::string Function;

private:
};

///
/// \class DataGroupPointer
///
class DEBLOAT_PRETTYPRINTER_EXPORT_API DataGroupPointer : public DataGroup {
public:
  DataGroupPointer(uint64_t x) : DataGroup(x) {}

  ~DataGroupPointer() override = default;

  DataGroup::Type getType() const override { return DataGroup::Type::Pointer; }

  uint64_t Content{0};

private:
};

///
/// \class DataGroupPointerDiff
///
class DEBLOAT_PRETTYPRINTER_EXPORT_API DataGroupPointerDiff : public DataGroup {
public:
  DataGroupPointerDiff(uint64_t x) : DataGroup(x) {}

  ~DataGroupPointerDiff() override = default;

  DataGroup::Type getType() const override { return DataGroup::Type::PointerDiff; }

  uint64_t Symbol1{0};
  uint64_t Symbol2{0};

private:
};

///
/// \class DataGroupString
///
class DEBLOAT_PRETTYPRINTER_EXPORT_API DataGroupString : public DataGroup {
public:
  DataGroupString(uint64_t x) : DataGroup(x) {}

  ~DataGroupString() override = default;

  DataGroup::Type getType() const override { return DataGroup::Type::String; }

  std::vector<uint8_t> StringBytes{};

private:
};

///
/// \class DataGroupRawByte
///
class DEBLOAT_PRETTYPRINTER_EXPORT_API DataGroupRawByte : public DataGroup {
public:
  DataGroupRawByte(uint64_t x) : DataGroup(x) {}

  ~DataGroupRawByte() override = default;

  DataGroup::Type getType() const override { return DataGroup::Type::RawByte; }

  uint8_t Byte;

private:
};
