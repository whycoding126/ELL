////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Machine Learning Library (EMLL)
//  File:     LinearPredictor.h (predictors)
//  Authors:  Ofer Dekel
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "IPredictor.h"

// linear
#include "DoubleVector.h"

// math
#include "Vector.h"

// datasets
#include "AutoDataVector.h"

// utilities
#include "IArchivable.h"

// stl
#include <cstdint>
#include <memory>

namespace emll
{
namespace predictors
{
    /// <summary> A linear binary predictor. </summary>
    class LinearPredictor : public IPredictor<double>, public utilities::IArchivable
    {
    public:
        /// <summary> Type of the data vector expected by this predictor type. </summary>
        using DataVectorType = data::AutoDataVector;

        /// <summary> Default Constructor. </summary>
        LinearPredictor();

        /// <summary> Constructs an instance of Linear. </summary>
        ///
        /// <param name="dim"> The dimension. </param>
        LinearPredictor(uint64_t dim);

        /// <summary> Returns the underlying DoubleVector. </summary>
        ///
        /// <returns> The underlying vector. </returns>
        math::ColumnVector<double>& GetWeights() { return _w; }

        /// <summary> Returns the underlying DoubleVector. </summary>
        ///
        /// <returns> The underlying vector. </returns>
        const math::ColumnVector<double>& GetWeights() const { return _w; } // TODO return ConstVectorReference?

        /// <summary> Returns the underlying bias. </summary>
        ///
        /// <returns> The bias. </returns>
        double& GetBias() { return _b; }

        /// <summary> Returns the underlying bias. </summary>
        ///
        /// <returns> The bias. </returns>
        double GetBias() const { return _b; }

        /// <summary> Gets the dimension of the linear predictor. </summary>
        ///
        /// <returns> The dimension. </returns>
        uint64_t GetDimension() const { return _w.Size(); }

        /// <summary> Returns the output of the predictor for a given example. </summary>
        ///
        /// <param name="example"> The data vector. </param>
        ///
        /// <returns> The prediction. </returns>
        double Predict(const DataVectorType& dataVector) const;

        /// <summary> Returns a vector of dataVector elements weighted by the predictor weights. </summary>
        ///
        /// <param name="example"> The data vector. </param>
        ///
        /// <returns> The weighted elements vector. </returns>
        DataVectorType GetWeightedElements(const DataVectorType& dataVector) const;

        /// <summary> Scales the linear predictor by a scalar </summary>
        ///
        /// <param name="scalar"> The scalar. </param>
        void Scale(double scalar);

        /// <summary> Resets the linear predictor to the zero vector with zero bias. </summary>
        void Reset();

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        static std::string GetTypeName() { return "LinearPredictor"; }

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        virtual std::string GetRuntimeTypeName() const override { return GetTypeName(); }

        /// <summary> Adds an object's properties to an `Archiver` </summary>
        ///
        /// <param name="archiver"> The `Archiver` to add the values from the object to </param>
        virtual void WriteToArchive(utilities::Archiver& archiver) const override;

        /// <summary> Sets the internal state of the object according to the archiver passed in </summary>
        ///
        /// <param name="archiver"> The `Archiver` to get state from </param>
        virtual void ReadFromArchive(utilities::Unarchiver& archiver) override;

    private:
        math::ColumnVector<double> _w;
        double _b;
    };
}
}
